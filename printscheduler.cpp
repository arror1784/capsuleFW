#include "printscheduler.h"
#include "bedcontrol.h"
#include "bedserialport.h"

#include "common/jsonutil.h"

#include <QQuickView>
#include <QObject>
#include <QQuickItem>
#include <QQmlContext>

#include <QDateTime>

#include <limits>

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

static constexpr auto floatError = std::numeric_limits<float>::epsilon() * 10;

PrintScheduler::PrintScheduler() :
    _LCDState(true)
{
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
    }else{
        _USBPortConnection = true;
    }

    addPrintingBed('A');

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

    _bedControl->defaultHeight = _printerSetting.defaultHeight;
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

    _bedControl->setBedCuringTime(3);
    _bedControl->setCuringTime(5000);

    _bedControl->setZHopHeightTime(3000);

    _bedControl->setMaxSpeed(500);
    _bedControl->setInitSpeed(0);

    _bedControl->setAccleSpeed(6,1);
    _bedControl->setDecelSpeed(30,1);
    _bedControl->setAccleSpeed(50,0);
    _bedControl->setDecelSpeed(50,0);

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
    auto jo = _printerSetting.motorTimeSpend;

    int time;

    if(jo.contains(_materialName)){
        time = 0;
        jo.insert(_materialName,0);
    }else{
        time = jo[_materialName];
    }
    jo[_materialName] = time + _printTime - (_bedControl->UVtime() + _bedControl->delayTime());
    _printerSetting.motorTimeSpend = jo;
    _printerSetting.save();
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
    ResinSetting::resinInfo materialSetting;

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

        _bedControl->maxHeight = _bedControl->defaultHeight + _printerSetting.heightOffset;

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
            QJsonObject jo = fd.object();

            materialSetting.resinLedOffset = Hix::Common::Json::getValue<double>(jo,"led_offset");
            materialSetting.contractionRatio = Hix::Common::Json::getValue<double>(jo,"contraction_ratio");
            materialSetting.layerHeight = Hix::Common::Json::getValue<double>(jo,"layer_height");

            materialSetting.bedCuringLayer = Hix::Common::Json::getValue<int>(jo,"bed_curing_layer");
            materialSetting.curingTime = Hix::Common::Json::getValue<int>(jo,"curing_time");
            materialSetting.zHopHeight = Hix::Common::Json::getValue<int>(jo,"z_hop_height");
            materialSetting.maxSpeed = Hix::Common::Json::getValue<int>(jo,"max_speed");
            materialSetting.initSpeed = Hix::Common::Json::getValue<int>(jo,"init_speed");
            materialSetting.upAccelSpeed = Hix::Common::Json::getValue<int>(jo,"up_accel_speed");
            materialSetting.upDecelSpeed = Hix::Common::Json::getValue<int>(jo,"up_decel_speed");
            materialSetting.downAccelSpeed = Hix::Common::Json::getValue<int>(jo,"down_accel_speed");
            materialSetting.downDecelSpeed = Hix::Common::Json::getValue<int>(jo,"down_decel_speed");
            materialSetting.bedCuringTime = Hix::Common::Json::getValue<int>(jo,"bed_curing_time");
            materialSetting.layerDelay = Hix::Common::Json::getValue<int>(jo,"layer_delay");
            materialSetting.material = Hix::Common::Json::getValue<int>(jo,"material");

        }else{
//            if(rs.getOpen())
                materialSetting = rs.resinList[QString::number(layer_height)];
//            else
//                return -5;
        }

        _bedControl->setLayerHeightTime((int)(layer_height * 1000));
        _layerHeight = layer_height;

        if(_bedMaxPrintNum > (dir.count() - 1)){

            return -4;
        }

        _bedCuringLayer = materialSetting.bedCuringLayer;
        _bedControl->setCuringTime(materialSetting.curingTime);
        _bedControl->setZHopHeightTime(materialSetting.zHopHeight);
        _bedControl->setMaxSpeed(materialSetting.maxSpeed);
        _bedControl->setInitSpeed(materialSetting.initSpeed);
        _bedControl->setAccleSpeed(materialSetting.upAccelSpeed,1);
        _bedControl->setDecelSpeed(materialSetting.upDecelSpeed,1);
        _bedControl->setAccleSpeed(materialSetting.downAccelSpeed,0);
        _bedControl->setDecelSpeed(materialSetting.downDecelSpeed,0);
        _bedControl->setBedCuringTime(materialSetting.bedCuringTime);
        _bedControl->layerDelay = materialSetting.layerDelay;

        _bedControl->setUVtime(0);

        emit sendToLCDSetImageScale(materialSetting.contractionRatio);

        double led = (_printerSetting.ledOffset / 100) *  materialSetting.resinLedOffset;
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

    std::filesystem::path dir(printFilePath.toStdString());
    if(std::filesystem::exists(dir) == true){
        std::filesystem::remove_all(dir);
    }
    if(!std::filesystem::create_directory(dir)){
        qDebug()<< " create folder fail" << printFilePath;
    }else{
        qDebug() << " create folder sucess";
    }
    qDebug() << "hello world" << this;

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
    deletePrintFolder();

    qDebug() << "debug delete print folder finish";

    if(unZipFiles(fileName)){
        emit sendToUIPrintSettingError(6);
        return;
    }
    qDebug() << "debug unzip finish";

    if(setupForPrint(materialName)){
        emit sendToUIPrintSettingError(3);
        return;
    }
    qDebug() << "debug setup finish";

    QStringList sl = fileName.split('/').last().split('.');
    sl.removeLast();
    _printName =  sl.join('.');
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

void PrintScheduler::receiveFromUISetHeightOffset(int value)
{
    _printerSetting.heightOffset = value;
    _printerSetting.save();
}

void PrintScheduler::receiveFromUISetLedOffset(double value)
{
    _printerSetting.ledOffset = value;
    _printerSetting.save();
}

void PrintScheduler::receiveFromUIPrintPause(){

//    _wsClient->sendPauseStart();
    _bedWork = BED_PAUSE_WORK;
    _printState = "pauseStart";
    emit sendToUIChangeToPauseStart();
}
void PrintScheduler::receiveFromUIGetMaterialList(){
    auto &a = _printerSetting.materialList;
    QVariant var = QVariant::fromValue(a);
    emit sendToUIMaterialList(QVariantList::fromVector(var.value<QVector<QVariant>>())); // it can work?????
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

int PrintScheduler::receiveFromUIGetHeightOffset()
{
    return _printerSetting.heightOffset;
}

double PrintScheduler::receiveFromUIGetLedOffset()
{
    return _printerSetting.ledOffset;
}

QString PrintScheduler::receiveFromUIGetMaterialOption(QString material){
    if(material == "Custom"){
        QFile file;
        QString val;

        file.setFileName(printFilePath + QStringLiteral("/resin.json"));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "info file open error";
            qDebug() << file.fileName();
            Logger::GetInstance()->write(file.fileName() + " file open error");
        }else{
            qDebug() << "resin file open sucess";
            Logger::GetInstance()->write(file.fileName() + " file open sucess");
        }
        val = file.readAll();
        file.close();

        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());

        return d.toJson();
    }else{
        ResinSetting rs(material);
        return rs.serialize();
    }
}

QString PrintScheduler::receiveFromUIGetPrintOption()
{
    QString val = printFilePath + QStringLiteral("/info.json");

    InfoSetting info(val);

    return info.serialize();
}

QString PrintScheduler::receiveFromUIGetInfoSetting(QString path)
{
    try {
        QString val;
        miniz_cpp::zip_file file(path.toStdString());
        val = QString::fromStdString(file.read("info.json"));

        return val;

    } catch (std::exception& e) {
        return "";
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

    sprintf(buffer,"G01 A%d M0",-(_printerSetting.defaultHeight + _printerSetting.heightOffset));
    bedSerialPort->sendCommand(buffer);
}

QString PrintScheduler::receiveFromUIGetVersion()
{
    return Version::getInstance().version;
}

QString PrintScheduler::receiveFromUIGetModelNo()
{
    return ModelNo::getInstance().modelNo;
}

void PrintScheduler::receiveFromUISetPrintTime(int time)
{
    _printTime = time;
}
