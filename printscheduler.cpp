#include "printscheduler.h"
#include "bedcontrol.h"
#include "bedserialport.h"

#include "common/jsonutil.h"

#include <QQuickView>
#include <QObject>
#include <QQuickItem>
#include <QQmlContext>

#include <QDateTime>

#include "printersetting.h"
#include "QJsonArray"
#include "QProcess"
#include "websocketclient.h"
#include "resinsetting.h"
#include "version.h"
#include "modelno.h"
#include "kinetimecalc.h"
#include "infosetting.h"

#include "zip/zip.h"

#include "ymodem.h"

#include "filesystem"

const QString printFilePath = "/opt/capsuleFW/print/printFilePath";


PrintScheduler::PrintScheduler() :
    _LCDState(true)
{
}

PrintScheduler::~PrintScheduler()
{
    qDebug() << "dis " << this;
}

void PrintScheduler::addPrintingBed(char name){
    _bedControl = new BedControl(name,bedSerialPort,this);

    bedSerialPort->setBedControl(_bedControl);
//    allBed.insert(name,_bedControl);
    _bedWork = BED_NOT_WORK;
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;
    _bedMaxPrintNum = 0;
    _isBusy = false;

    initPrint();

    _bedControl->defaultHeight = PrinterSetting::getInstance().getPrintSetting("default_height").toInt();
}

int PrintScheduler::addSerialPort(){

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        if(info.portName().contains(QStringLiteral("USB")) /*|| info.portName().contains(QStringLiteral("ACM"))*/){
            bedSerialPort = new BedSerialport(info.portName(),this);
            bedSerialPort->serialOpen();
            _portPath = info.portName();
            return 0;
        }
    }
    return 1;
}

int PrintScheduler::saveFile(QString path, QByteArray byte){

    QFile saveFile(path);

    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "save file open error";
        return -1;
    }

    saveFile.write(byte);
    saveFile.close();
    return 0;
}

void PrintScheduler::run(){

    _wsClient = new WebSocketClient(QUrl(QStringLiteral("ws://localhost:8000/ws/printer")));
    QObject::connect(_wsClient,&WebSocketClient::startByWeb,this,&PrintScheduler::receiveFromUIPrintStart);
    QObject::connect(_wsClient,&WebSocketClient::pauseByWeb,this,&PrintScheduler::receiveFromUIPrintPause);
    QObject::connect(_wsClient,&WebSocketClient::resumeByWeb,this,&PrintScheduler::receiveFromUIPrintResume);
    QObject::connect(_wsClient,&WebSocketClient::finishByWeb,this,&PrintScheduler::receiveFromUIPrintFinish);
    QObject::connect(_wsClient,&WebSocketClient::getMaterialListbyWeb,this,&PrintScheduler::receiveFromUIGetMaterialList);
    QObject::connect(_wsClient,&WebSocketClient::getPrintInfoByWeb,this,&PrintScheduler::receiveFromUIGetPrintInfoToWeb);


    QObject::connect(this,&PrintScheduler::sendToUIUpdateProgress,_wsClient,&WebSocketClient::updateProgressToWeb);

    QObject::connect(this,&PrintScheduler::sendToUIChangeToPrint,_wsClient,&WebSocketClient::changeToPrintToWeb);
    QObject::connect(this,&PrintScheduler::sendToUIChangeToPauseStart,_wsClient,&WebSocketClient::changeToPauseStartToWeb);
    QObject::connect(this,&PrintScheduler::sendToUIChangeToPauseFinish,_wsClient,&WebSocketClient::changeToPauseFinishToWeb);
    QObject::connect(this,&PrintScheduler::sendToUIChangeToResume,_wsClient,&WebSocketClient::changeToResumeToWeb);
    QObject::connect(this,&PrintScheduler::sendToUIChangeToQuit,_wsClient,&WebSocketClient::changeToQuitToWeb);
    QObject::connect(this,&PrintScheduler::sendToUIChangeToPrintFinish,_wsClient,&WebSocketClient::changeToPrintFinishToWeb);
    QObject::connect(this,&PrintScheduler::sendToUIChangeToPrintWorkError,_wsClient,&WebSocketClient::changeToPrintWorkErrorToWeb);
    QObject::connect(this,&PrintScheduler::sendToUIChangeToPrintWorkErrorFinish,_wsClient,&WebSocketClient::changeToPrintWorkErrorFinishToWeb);
    QObject::connect(this,&PrintScheduler::sendToUIPrintSettingError,_wsClient,&WebSocketClient::changeToPrintSettingErrorToWeb);

    QObject::connect(this,&PrintScheduler::sendToUIMaterialList,_wsClient,&WebSocketClient::materialListToWeb);

    QObject::connect(this,&PrintScheduler::sendToUIEnableTimer,_wsClient,&WebSocketClient::enableTimer);

    QObject::connect(this,&PrintScheduler::sendToUIPrintInfo,_wsClient,&WebSocketClient::getPrintInfoToWeb);
    QObject::connect(this,&PrintScheduler::sendToUISetTotalTime,_wsClient,&WebSocketClient::setTotalTime);


    _wsClient->open();

    if(addSerialPort()){
        _USBPortConnection = false;
        _printState = "USBCONNECTIONERROR";
        emit sendToUIPortOpenError();
        while(true)
            QThread::exec();
    }else{
        _USBPortConnection = true;
    }

    addPrintingBed('A');

    qDebug() << "print scheduler" << QThread::currentThread();
    while(true)
        QThread::exec();
}

QString PrintScheduler::materialName() const
{
    return _materialName;
}

void PrintScheduler::initBed(){
    _bedWork = BED_WORK;
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_AUTOHOME);

    imageChange();
}

void PrintScheduler::bedFinish(){


    _bedWork = BED_FINISH_WORK;
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;

    _printState = "ready";
//        _bedError = false;
    _enableTimer = false;
    emit sendToUIEnableTimer(false);
//    _wsClient->sendEnableTimer(false);
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_FINISH);


}
void PrintScheduler::bedError(){

    _bedWork = BED_ERROR_WORK;
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;
//        emit sendToUIPrintFinish();
//        _bedError = false;
    _enableTimer = false;
    emit sendToUIEnableTimer(false);
//    _wsClient->sendEnableTimer(false);
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_FINISH);

}

void PrintScheduler::initPrint()
{
    ResinSetting rs("default");

    _bedControl->setBedCuringTime(rs.getResinSetting("bed_curing_time").toInt());
    _bedControl->setCuringTime(rs.getResinSetting("curing_time").toInt());

    _bedControl->setZHopHeightTime(rs.getResinSetting("z_hop_height").toInt());

    _bedControl->setMaxSpeed(rs.getResinSetting("max_speed").toInt());
    _bedControl->setInitSpeed(rs.getResinSetting("init_speed").toInt());

    _bedControl->setAccleSpeed(rs.getResinSetting("up_accel_speed").toInt(),1);
    _bedControl->setDecelSpeed(rs.getResinSetting("up_decel_speed").toInt(),1);
    _bedControl->setAccleSpeed(rs.getResinSetting("down_accel_speed").toInt(),0);
    _bedControl->setDecelSpeed(rs.getResinSetting("down_decel_speed").toInt(),0);

    _bedControl->setUVtime(0);

    bedSerialPort->sendCommand("H10");
    bedSerialPort->sendCommand("H91");
}

void PrintScheduler::printLayer(){

    if(_bedWork == BED_WORK && _bedMoveFinished == PRINT_MOVE_LAYER_OK){
        _bedMoveFinished = PRINT_MOVE_READY;

        if(_bedPrintImageNum == _bedMaxPrintNum){
            receiveFromUIPrintFinish();
            return;
        }else if(QFile::exists(printFilePath + "/" + QString::number(_bedPrintImageNum) + _fileExtension) == false){
//            receiveFromUIPrintFinishError();
            _bedError = true;
            _printState = "error";
            emit sendToUIChangeToPrintWorkError();
        }
        _bedPrintImageNum++;

        _progress = ((double)_bedPrintImageNum/(double)_bedMaxPrintNum) * 100;
        emit sendToUIUpdateProgress(_progress);
//        _wsClient->sendProgreeUpdate(((double)_bedPrintImageNum/(double)_bedMaxPrintNum) * 100);

        if(_bedPrintImageNum <= _bedCuringLayer){
            _bedControl->receiveFromPrintScheduler(PRINT_MOVE_BEDCURRENT);
        }else{
            _bedControl->receiveFromPrintScheduler(PRINT_DLP_WORKING);
        }
    }
}
int PrintScheduler::imageChange(){

    QString fullPath = QStringLiteral("file:/") + printFilePath + "/" + QString::number(_bedPrintImageNum) + _fileExtension;
    Logger::GetInstance()->write("print image path : " + fullPath);

    emit sendToLCDChangeImage(fullPath);

    return 0;
}
void PrintScheduler::receiveFromBedControl(int receive){
    switch (receive) {
        case PRINT_DLP_WORK_FINISH:
            imageChange();
            break;
        case PRINT_MOVE_INIT_OK:
//            _wsClient->sendEnableTimer(true);
//            _wsClient->sendSetTimerTime();
            _enableTimer = true;
            emit sendToUIEnableTimer(true);
        case PRINT_MOVE_LAYER_OK:
            if(_bedError){
                receiveFromUIPrintFinishError();
                break;
            }
            if(_bedWork == BED_PAUSE_WORK){
                _printState = "pause";
                _elapsedTime = _elapsedTime + (QDateTime::currentDateTime().toMSecsSinceEpoch() - _lastStartTime);

                _enableTimer = false;
                emit sendToUIEnableTimer(false);
                emit sendToUIChangeToPauseFinish();
//                _wsClient->sendPauseFinish();
                _bedWork = BED_PAUSE;
            }
            _bedMoveFinished = PRINT_MOVE_LAYER_OK;
            if(_bedPrintImageNum == _bedCuringLayer){
                emit sendToUIFirstlayerStart();
            }else if(_bedPrintImageNum == (_bedCuringLayer + 1)){
                emit sendToUIFirstlayerFinish();
            }

            printLayer();
            break;
        case PRINT_MOVE_AUTOHOME_OK:
            break;
        case PRINT_MOVE_FINISH_OK:    qDebug() << QThread::currentThreadId();

            _bedWork = BED_NOT_WORK;
            _bedMoveFinished = PRINT_MOVE_NULL;
            if(_bedError){
                emit sendToUIChangeToPrintWorkErrorFinish();
//                _wsClient->sendFinish();
                _printState = "ready";
                _bedError = false;
            }else{
                emit sendToUIChangeToPrintFinish();
                _printState = "ready";
//                _wsClient->sendFinish();
            }
            setMotorSpendtime();
            break;
        case PRINT_PAUSE:
            break;
        case PRINT_RESUME:
            break;
    }
}
void PrintScheduler::setMotorSpendtime(){
    QJsonObject jo = PrinterSetting::getInstance().getPrintSetting("motor_time_spend").toObject();
    int time;

    if(jo[_materialName].isNull()){
        time = 0;
        jo.insert(_materialName,0);
    }else{
        time = jo[_materialName].toInt();
    }
    jo[_materialName] = time + _printTime - (_bedControl->UVtime() + _bedControl->delayTime());
    PrinterSetting::getInstance().setPrintSetting("motor_time_spend",jo);
}
void PrintScheduler::receiveFromSerialPort(int state){

    if (state == MOVE_OK) {
        emit sendToUIMoveOk();
    }else if (state == SHUTDOWN) {
        if(_isBusy)
            emit sendToUIExitError();
        else    qDebug() << QThread::currentThreadId();

            emit sendToUIExit();
    }else if(state == LCD_ON){
        emit sendToUILCDState(true);
    }else if(state == LCD_OFF){

        _LCDState = false;

        if(_bedWork == BED_FINISH_WORK || _bedWork == BED_NOT_WORK || _bedWork == BED_ERROR_WORK){

        }else{
            _bedError = true;
            _printState = "error";
            emit sendToUIChangeToPrintWorkError();
        }
        emit sendToUILCDState(false);
    }
}

void PrintScheduler::printStart()
{
//    _wsClient->sendStart();
    _printState = "print";
    _lastStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    emit sendToUIChangeToPrint();
    emit sendToUIPrintInfo(_printState, _materialName, _printName, _layerHeight, 0, _totalPrintTime, _progress,_enableTimer);
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;
    initBed();
}

void PrintScheduler::printResume()
{
//    _wsClient->sendResume();
    _printState = "print";
    _bedWork = BED_WORK;
    printLayer();
}

void PrintScheduler::receiveFromUIBusySet(bool bs)
{
    _isBusy = bs;
}

void PrintScheduler::receiveFromUpdaterFirmUpdate(QString path)
{
    std::function<void()> f = [this,path](){
        QSerialPort *sp = new QSerialPort(_portPath);
        sp->setPortName(_portPath);
        sp->setBaudRate(QSerialPort::Baud115200);

        while (1){
            bedSerialPort->sendCommand("H101");
            QThread::msleep(1000);

            bedSerialPort->serialClose();

            if(!sp->open(QIODevice::ReadWrite)){
                qDebug() << _portPath << "usb open error";
            }

            YMODEM ym(sp);

            int a = ym.yTransmit(path);

            if(a){
                sp->close();
                bedSerialPort->serialOpen();
                QThread::msleep(3000);
                continue;
            }else{
                sp->close();
                bedSerialPort->serialOpen();
                QThread::msleep(5000);
                initPrint();
                break;
            }
        }

        emit MCUFirmwareUpdateFinished();
    };
    QMetaObject::invokeMethod(bedSerialPort,f,Qt::AutoConnection);
}

void PrintScheduler::receiveFromUIShutdown()
{
    bedSerialPort->sendCommand("H200");
    qDebug() << "shutdown";
    QStringList arguments;
    arguments.append("-h");
    arguments.append("now");
    QProcess::execute("bash -c \"echo rasp | sudo -S shutdown -h now > /home/pi/out 2>&1\"");
}

int PrintScheduler::copyFilesPath(QString src, QString dst)
{
    QRegularExpression svgRe("\\d{1,4}"+_fileExtension);
    QDir dir(src);
    int count = 0;
    if (! dir.exists())
        return -1;

    foreach (QString f, dir.entryList(QDir::Files)) {
        if(svgRe.match(f).hasMatch() == true){
            QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
            count++;
        }else if(f.contains("info.json")){
            QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
            count++;
        }else if(f.contains("resin.json")){
            QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
        }
    }

    return count;
}

int PrintScheduler::copyProject(QString path)
{
    QFile file;
    QString val;
    QString filePath = path;
    int dirCount = 0;


    dirCount = copyFilesPath(filePath,printFilePath);
    if(dirCount == -1){
        return -1;
    }
    return 0;
}
int PrintScheduler::donwloadFiles(QJsonObject byte)
{
//    QJsonObject &ja = byte;
    //file save

    foreach(const QString& key, byte.keys()){
        if(saveFile(printFilePath + "/" + key, QByteArray::fromBase64(byte.value(key).toString().split(",")[1].toUtf8()))){
            return -1;
        }
    }
    return 0;
}

bool PrintScheduler::isCustom(QString path)
{
    QString val;

    qDebug() << path;
    try {

        miniz_cpp::zip_file file(path.toStdString());
        if(file.has_file("resin.json")){
            return true;
        }else{
            return false;
        }

    } catch (std::exception e) {
        return false;
    }
}

int PrintScheduler::setupForPrint(QString materialName)
{
    QFile file;
    QString val;
    QString filePath = printFilePath;
    QString infoPath = filePath + QStringLiteral("/info.json");
    int error = 0;

    QJsonDocument d;
    QJsonObject materialSetting;

    ResinSetting rs(materialName);

    QFile f;
    QString fval;
    QJsonDocument fd;

    QDir dir(filePath);
    dir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );

    _progress = 0;
    _lastStartTime = 0;
    _elapsedTime = 0;
    _layerHeight = 0.0;
    _printState = "ready";
    _totalPrintTime = 0;


    try {
        InfoSetting info(infoPath);
        info.parse();

        _bedControl->maxHeight = _bedControl->defaultHeight + PrinterSetting::getInstance().getPrintSetting("height_offset").toInt();

        _bedMaxPrintNum = info.totalLayer;

        auto layer_height = round(info.layerHeight * 10000) / 10000;

        if(materialName == "Custom"){
            f.setFileName(filePath + QStringLiteral("/resin.json"));
            if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
                qDebug() << "resin file open error";
                Logger::GetInstance()->write(f.fileName() + " file open error");
                return -2;
            }
            fval = f.readAll();
            f.close();

            fd = QJsonDocument::fromJson(fval.toUtf8());

            materialSetting = fd.object();
        }else{
            if(rs.getOpen())
                materialSetting = rs.getJsonObjectLayerHeight(layer_height);
            else
                return -5;
        }

        _bedControl->setLayerHeightTime((int)(layer_height * 1000));
        _layerHeight = layer_height;

        if(_bedMaxPrintNum > (dir.count() - 1)){

            return -4;
        }

        _bedCuringLayer = Hix::Common::Json::getValue<int>(materialSetting,"bed_curing_layer");
        _bedControl->setCuringTime(Hix::Common::Json::getValue<int>(materialSetting,"curing_time"));
        _bedControl->setZHopHeightTime(Hix::Common::Json::getValue<int>(materialSetting,"z_hop_height"));
        _bedControl->setMaxSpeed(Hix::Common::Json::getValue<int>(materialSetting,"max_speed"));
        _bedControl->setInitSpeed(Hix::Common::Json::getValue<int>(materialSetting,"init_speed"));
        _bedControl->setAccleSpeed(Hix::Common::Json::getValue<int>(materialSetting,"up_accel_speed"),1);
        _bedControl->setDecelSpeed(Hix::Common::Json::getValue<int>(materialSetting,"up_decel_speed"),1);
        _bedControl->setAccleSpeed(Hix::Common::Json::getValue<int>(materialSetting,"down_accel_speed"),0);
        _bedControl->setDecelSpeed(Hix::Common::Json::getValue<int>(materialSetting,"down_decel_speed"),0);
        _bedControl->setBedCuringTime(Hix::Common::Json::getValue<int>(materialSetting,"bed_curing_time"));
        _bedControl->layerDelay = Hix::Common::Json::getValue<int>(materialSetting,"layer_delay");

        _bedControl->setUVtime(0);

        emit sendToLCDSetImageScale(Hix::Common::Json::getValue<double>(materialSetting,"contraction_ratio"));

        double led = (PrinterSetting::getInstance().getPrintSetting("led_offset").toDouble() / 100) *  Hix::Common::Json::getValue<int>(materialSetting,"led_offset");
        _bedControl->setLedOffset(led * 10);

        //    KineTimeCalc kinCalc(setting["total_layer"].toInt(), materialSetting["bed_curing_layer"].toInt(), materialSetting["layer_delay"].toInt(), setting["layer_height"].toDouble(),
        //            materialSetting["z_hop_height"].toInt() / 1000,materialSetting["init_speed"].toInt(), materialSetting["max_speed"].toInt(), materialSetting["up_accel_speed"].toInt(),
        //            materialSetting["up_decel_speed"].toInt(), materialSetting["down_accel_speed"].toInt(), materialSetting["down_decel_speed"].toInt(),
        //                 materialSetting["bed_curing_time"].toInt(), materialSetting["curing_time"].toInt());

        //    _totalPrintTime = kinCalc.layerPrintTime();


    } catch (std::exception &e) {
        return -3;
    }


    return 0;
}



int PrintScheduler::deletePrintFolder()
{

//    std::filesystem::path dir(printFilePath.toStdString());
//    if(std::filesystem::exists(dir) == true){
//        std::filesystem::remove_all(dir);
//    }
//    if(!std::filesystem::create_directory(dir)){
//        qDebug()<< " create folder fail" << printFilePath;
//    }else{
//        qDebug() << " create folder sucess";
//    }
    qDebug() << "hello world" << this;

}

int PrintScheduler::sayHello()
{
    qDebug() << "say hello";
}


int PrintScheduler::unZipFiles(QString path)
{
    try {
        miniz_cpp::zip_file file(path.toStdString());

        file.extractall(printFilePath.toStdString());
    } catch (std::exception e) {
        return -1;
    }
    return 0;
}

void PrintScheduler::receiveFromQMLPrintStart(QString fileName, QString materialName)
{
    qDebug() << fileName;
//    std::lock_guard<std::mutex> ml(_mPrint);
    if(!_LCDState){
        emit sendToUIPrintSettingError(1);
        return;
    }
    if(_printState != "ready"){
        emit sendToUIPrintSettingError(4);
        return;
    }
    if(!_USBPortConnection){
        emit sendToUIPrintSettingError(5);
        return;
    }
//    deletePrintFolder();
    qDebug() << this;

    qDebug() << QThread::currentThreadId();
    sayHello();

    qDebug() << "debug delete print folder finish";

//    if(unZipFiles(fileName)){
//        emit sendToUIPrintSettingError(6);
//        return;
//    }
    qDebug() << "debug unzip finish";

    if(setupForPrint(materialName)){
        emit sendToUIPrintSettingError(3);
        return;
    }
    qDebug() << "debug setup finish";

//    QStringList sl = fileName.split('/').last().split('.');
//    sl.removeLast();
//    _printName =  sl.join('.');
    _printName =  fileName;
    _materialName = materialName;

    printStart();
}

void PrintScheduler::receiveFromUIPrintStart(QString fileName, QString materialName, QJsonObject byte)
{
    qDebug() << fileName << materialName;
//    std::lock_guard<std::mutex> ml(_mPrint);
    if(!_LCDState){
        emit sendToUIPrintSettingError(1);
        return;
    }
    if(!_USBPortConnection){
        emit sendToUIPrintSettingError(5);
        return;
    }
    if(_printState != "ready"){
        emit sendToUIPrintSettingError(4);
        return;
    }

    deletePrintFolder();

    if(donwloadFiles(byte)){
        emit sendToUIPrintSettingError(2);
        return;
    }
    if(unZipFiles(printFilePath + "/" + fileName)){
        emit sendToUIPrintSettingError(6);
        return;
    }

    if(setupForPrint(materialName)){
        emit sendToUIPrintSettingError(3);
        return;
    }
//    QStringList sl = fileName.split('/').last().split('.');
//    sl.removeLast();
//    _printName =  sl.join('.');
    _printName =  fileName;
    _materialName = materialName;

    printStart();
}

void PrintScheduler::receiveFromUIPrintAgain()
{
    if(!_LCDState){
        emit sendToUIPrintSettingError(1);
        return;
    }
    if(setupForPrint(_materialName)){
        emit sendToUIPrintSettingError(3);
        return;
    }
    qDebug() << _printName << _materialName;

    printStart();
}

void PrintScheduler::receiveFromUIPrintResume(){

    if(_bedWork == BED_PAUSE){
        printResume();
        _lastStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        _enableTimer = true;
        _printState = "print";
        emit sendToUIEnableTimer(true);
        emit sendToUIChangeToResume();
    }/*else{
        printStart();
    }*/
}

void PrintScheduler::receiveFromUIPrintFinish(){
    bedFinish();
    _printState = "quit";
    emit sendToUIChangeToQuit();
}
void PrintScheduler::receiveFromUIPrintFinishError(){
    bedError();
}
void PrintScheduler::receiveFromUIPrintPause(){

//    _wsClient->sendPauseStart();
    _bedWork = BED_PAUSE_WORK;
    _printState = "pauseStart";
    emit sendToUIChangeToPauseStart();
}
void PrintScheduler::receiveFromUIGetMaterialList(){
    QJsonArray a = PrinterSetting::getInstance().getResinList();
    emit sendToUIMaterialList(a.toVariantList());
}

void PrintScheduler::receiveFromUIGetPrintInfoToWeb()
{
    int eT;
    if(_printState == "print"){
        eT = _elapsedTime + (QDateTime::currentDateTime().toMSecsSinceEpoch() - _lastStartTime);
    }else{
        eT = _elapsedTime;
    }

    emit sendToUIPrintInfo(_printState, _materialName, _printName, _layerHeight, eT, _totalPrintTime, _progress,_enableTimer);
}

void PrintScheduler::receiveFromUIConnected()
{
    emit sendToUIPortOpenError();
//    emit sendToUI
}
QVariant PrintScheduler::receiveFromUIGetPrinterOption(QString key){
    return PrinterSetting::getInstance().getPrintSetting(key).toVariant();
}

void PrintScheduler::receiveFromUISetPrinterOption(QString key,double value){
    PrinterSetting::getInstance().setPrintSetting(key,value);
}
void PrintScheduler::receiveFromUISetPrinterOption(QString key,int value){
    PrinterSetting::getInstance().setPrintSetting(key,value);
}
void PrintScheduler::receiveFromUISetPrinterOption(QString key,QString value){
    PrinterSetting::getInstance().setPrintSetting(key,value);
}

QVariant PrintScheduler::receiveFromUIGetMaterialOption(QString material,QString key){
    if(material == "Custom"){
        QFile file;
        QString val;

        file.setFileName(printFilePath + QStringLiteral("/resin.json"));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "info file open error";
            qDebug() << file.fileName();
            Logger::GetInstance()->write(file.fileName() + " file open error");
            return -2;
        }else{
            qDebug() << "resin file open sucess";
            Logger::GetInstance()->write(file.fileName() + " file open sucess");
        }
        val = file.readAll();
        file.close();

        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject setting = d.object();

        return setting[key].toVariant();
    }else{
        ResinSetting rs(material);
        return rs.getResinSetting(key).toVariant();
    }
}
QVariant PrintScheduler::receiveFromUIGetMaterialOptionFromPath(QString path,QString key){

    try {
        QString val;
        miniz_cpp::zip_file file(path.toStdString());
        val = QString::fromStdString(file.read("resin.json"));

        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject setting = d.object();

        return setting[key].toVariant();

    } catch (std::exception e) {
        return 0;
    }
}

QVariant PrintScheduler::receiveFromUIGetPrintOption(QString key)
{
    QFile file;
    QString val;

    file.setFileName(printFilePath + QStringLiteral("/info.json"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "info file open error";
        qDebug() << file.fileName();
        Logger::GetInstance()->write(file.fileName() + " file open error");
        return -2;
    }else{
        qDebug() << "info file open sucess";
        Logger::GetInstance()->write(file.fileName() + " file open sucess");
    }
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject setting = d.object();

    return setting[key].toVariant();
}
QVariant PrintScheduler::receiveFromUIGetPrintOptionFromPath(QString key, QString path)
{
    try {
        QString val;
        miniz_cpp::zip_file file(path.toStdString());
        val = QString::fromStdString(file.read("info.json"));

        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject setting = d.object();

        return setting[key].toVariant();

    } catch (std::exception& e) {
        return 0;
    }

}

void PrintScheduler::receiveFromUISetTotalPrintTime(int time)
{
    _totalPrintTime = time;
    emit sendToUISetTotalTime(time);
}

void PrintScheduler::receiveFromUIGoHome(){
    bedSerialPort->sendCommand("G02 A-15000 M1");
}
void PrintScheduler::receiveFromUIAutoHome(){
    bedSerialPort->sendCommand("G28 A225");
}
void PrintScheduler::receiveFromUIMoveMicro(int micro){
    char buffer[50] = {0};

    sprintf(buffer,"G01 A%d M0",-micro);
    bedSerialPort->sendCommand(buffer);
}
void PrintScheduler::receiveFromUIMoveMaxHeight(){
    char buffer[50] = {0};

    sprintf(buffer,"G01 A%d M0",-(PrinterSetting::getInstance().getPrintSetting("default_height").toInt() + PrinterSetting::getInstance().getPrintSetting("height_offset").toInt()));
    bedSerialPort->sendCommand(buffer);
}

QString PrintScheduler::receiveFromUIGetVersion()
{
    return Version::getInstance().getVersion();
}

QString PrintScheduler::receiveFromUIGetModelNo()
{
    return ModelNo::getInstance().getModelNo();
}

void PrintScheduler::receiveFromUISetPrintTime(int time)
{
    _printTime = time;
}
