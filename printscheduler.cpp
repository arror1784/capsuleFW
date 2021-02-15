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
#include "transimagergb.h"

#include "zip/zip.h"

#include "ymodem.h"
#include "printimage.h"
#include "printimagecontrol.h"

#include <filesystem>

const QString printFilePath = "/opt/capsuleFW/print/printFilePath";

static constexpr auto floatError = std::numeric_limits<float>::epsilon() * 10;

PrintScheduler::PrintScheduler(PrintImageControl* pi) :
    _LCDState(true)
{
    _printImageControl = pi;

    _printerSetting.parse();
    _version.parse();
#ifndef TEST_WITHOUT_SERIAL
    if(addSerialPort()){
        _USBPortConnection = false;
        _printState = "USBCONNECTIONERROR";
        emit sendToUIPortOpenError(true);
        return;
    }else{
        _USBPortConnection = true;
    }
#else
    bedSerialPort = new BedSerialport(this);
    _USBPortConnection = true;
#endif
    //check product
    _printImageControl->imageRotate(0);
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

void PrintScheduler::setTotaltime(uint64_t moveTime)
{
    int totalTime = 0;

    totalTime += _bedCuringLayer * _bedCuringTime;
    totalTime += (_bedMaxPrintNum - _bedCuringLayer) * _curingTime;

    totalTime += moveTime * _bedMaxPrintNum;
    totalTime += _printDelay * _bedMaxPrintNum;

    _totalPrintTime = totalTime;

    if(_totalTimeCalc){
        _totalTimeCalc = false;
        emit sendToUISetTotalTime(totalTime);
    }
}

void PrintScheduler::sendAutoReboot(bool value)
{
    emit sendToUIAutoReboot(value);
}

void PrintScheduler::receiveFromUIPrintUnlock()
{
    emit sendToUIChangeState("unlock");
    _printState = "ready";
}

void PrintScheduler::initBed(){
    _bedWork = BED_WORK;

    _printImageControl->imageChange(0);
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_AUTOHOME);

    return;
}

void PrintScheduler::bedFinish(){

    _bedWork = BED_FINISH_WORK;
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;

    _printState = "quit";
//        _bedError = false;
    _enableTimer = false;
    emit sendToUIEnableTimer(false);
    _printImageControl->imageSetBlack();
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_FINISH);

    return;
}
void PrintScheduler::bedError(){

    _bedWork = BED_ERROR_WORK;
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;
//        emit sendToUIPrintFinish();
//        _bedError = false;
    _enableTimer = false;
    emit sendToUIEnableTimer(false);
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_FINISH);

    return;
}

void PrintScheduler::initPrint()
{
    _bedControl->setBedCuringTime(3);
    _bedControl->setCuringTime(5000);

    _bedControl->setZHopHeightTime(3000);

    _bedControl->setMaxSpeed(500);
    _bedControl->setInitSpeed(0);

    _bedControl->setAccleSpeed(80,1);
    _bedControl->setDecelSpeed(80,1);
    _bedControl->setAccleSpeed(80,0);
    _bedControl->setDecelSpeed(80,0);

    _bedControl->setUVtime(0);

    bedSerialPort->sendCommand("H10");
    bedSerialPort->sendCommand("H91");
    return;
}

void PrintScheduler::initPrintinfo()
{
    _progress = 0;
    _lastStartTime = 0;
    _elapsedTime = 0;
    _layerHeight = 0.0;
    _printState = "ready";
    _totalPrintTime = 0;
    _totalTimeCalc = true;
}

void PrintScheduler::printLayer(){

    if(_bedWork == BED_WORK && _bedMoveFinished == PRINT_MOVE_LAYER_OK){
        _bedMoveFinished = PRINT_MOVE_READY;

        if(_bedPrintImageNum == _bedMaxPrintNum){
            receiveFromUIPrintStateChange("finish");
            return;
        }else if(QFile::exists(printFilePath + "/" + QString::number(_bedPrintImageNum) + ".png") == false){
//            receiveFromUIPrintFinishError();
            _bedError = true;
            _printState = "error";
            emit sendToUIChangeState("printError");
        }
        _bedPrintImageNum++;

        _progress = ((double)_bedPrintImageNum/(double)_bedMaxPrintNum) * 100;
        emit sendToUIUpdateProgress(_progress);

        _printImageControl->waitImageWrote();

        if(_bedPrintImageNum <= _bedCuringLayer){
            _bedControl->receiveFromPrintScheduler(PRINT_MOVE_BEDCURRENT);
        }else{
            _bedControl->receiveFromPrintScheduler(PRINT_DLP_WORKING);
        }

    }
}
void PrintScheduler::receiveFromBedControl(int receive){
    switch (receive) {
        case PRINT_DLP_WORK_FINISH:
            _printImageControl->imageChange(_bedPrintImageNum);
            break;
        case PRINT_MOVE_INIT_OK:
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
                emit sendToUIChangeState("pauseFinish");
                _bedWork = BED_PAUSE;
            }
            _bedMoveFinished = PRINT_MOVE_LAYER_OK;

            printLayer();
            break;
        case PRINT_MOVE_AUTOHOME_OK:
            break;
        case PRINT_MOVE_FINISH_OK:

            _bedWork = BED_NOT_WORK;
            _bedMoveFinished = PRINT_MOVE_NULL;
            if(_bedError){
                emit sendToUIChangeState("printErrorFinish");
                _printState = "lock";
                _bedError = false;
            }else{
                emit sendToUIChangeState("printFinish");
                _printState = "lock";
            }
            setMotorSpendtime();
            break;
        case PRINT_PAUSE:
            break;
        case PRINT_RESUME:
            break;
    }
    return;
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
    return;
}
void PrintScheduler::receiveFromSerialPort(int state){

    if (state == MOVE_OK) {
        emit sendToUIMoveOk();
    }else if (state == SHUTDOWN) {
        if(_isBusy)
            emit sendToUIExit(false);
        else
            emit sendToUIExit(true);
    }else if(state == LCD_ON){
        emit sendToUILCDState(true);
    }else if(state == LCD_OFF){

        _LCDState = false;

        if(_bedWork == BED_FINISH_WORK || _bedWork == BED_NOT_WORK || _bedWork == BED_ERROR_WORK){

        }else{
            _bedError = true;
            _printState = "error";
            emit sendToUIChangeState("printError");
        }
        emit sendToUILCDState(false);
    }
    return;
}

void PrintScheduler::printStart()
{
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
    return;
}

void PrintScheduler::receiveFromUIAutoReboot()
{
    bedSerialPort->sendCommand("H111");
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
    QRegularExpression svgRe("\\d{1,4}.png");
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
int PrintScheduler::donwloadFiles(QJsonObject& byte)
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

int PrintScheduler::setupForPrint(QString materialName)
{
    QFile file;
    QString val;
    QString filePath = printFilePath;
    QString infoPath = filePath + QStringLiteral("/info.json");
    QString resinPath = filePath + QStringLiteral("/resin.json");

    QJsonDocument d;
    ResinSetting::resinInfo materialSetting;

    ResinSetting rs(materialName);
    rs.parse();

    QFile f;
    QString fval;
    QJsonDocument fd;

    QDir dir(filePath);
    dir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );

    try {
        InfoSetting info(infoPath);
        info.parse();

        _bedControl->maxHeight = _bedControl->defaultHeight + _printerSetting.heightOffset;

        _bedMaxPrintNum = info.totalLayer;

        auto layer_height = round(info.layerHeight * 10000) / 10000;

        if(materialName == "Custom"){

            f.setFileName(resinPath);
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

        }else{
            if(rs.resinList.contains(QString::number(layer_height))){
                materialSetting = rs.resinList[QString::number(layer_height)];
            }else{
                return -6;
            }
        }

        std::filesystem::path resinJson = resinPath.toStdString();
        int dirCount = 0;
        if(std::filesystem::exists(resinJson)){
            dirCount = 2;
        }else{
            dirCount = 1;

        }
        if(_bedMaxPrintNum != (dir.count() - dirCount)){
            return -4;
        }

        _bedControl->setLayerHeightTime((int)(layer_height * 1000));
        _layerHeight = layer_height;



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

        _bedCuringTime = materialSetting.bedCuringTime;
        _curingTime = materialSetting.curingTime;
        _printDelay = materialSetting.layerDelay;

        _bedControl->setUVtime(0);

        _printImageControl->imageScale(materialSetting.contractionRatio);

        double led = (_printerSetting.ledOffset / 100) *  materialSetting.resinLedOffset;
        _bedControl->setLedOffset(led * 10);

        if(ProductSetting::getInstance().product == ProductType::C10){
            qDebug() << "C10";
            _printImageControl->imageRotate(90);
            _printImageControl->imageWidhtHeight(2560,1440);
        }else if(ProductSetting::getInstance().product == ProductType::L10){
            qDebug() << "L10";
            _printImageControl->imageRotate(0);
            _printImageControl->imageWidhtHeight(540,2560);
        }
    } catch (std::runtime_error &e) {
        qDebug() << e.what();
        return -3;
    }


    return 0;
}

void PrintScheduler::deletePrintFolder()
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
    return;
}
int PrintScheduler::unZipFiles(QString path)
{
    try {
        std::string target = path.toStdString();

        miniz_cpp::zip_file file(target);

        file.extractall(printFilePath.toStdString());
    } catch (std::exception e) {
        return -1;
    }
    return 0;
}

void PrintScheduler::receiveFromUIPrintStart(QVariantList args)
{
    auto size = args.size();
    QString fileName;
    QString materialName;

    if(!_LCDState){
        emit sendToUIPrintSettingError(1);
        return;
    }
    if(!_USBPortConnection){
        emit sendToUIPrintSettingError(5);
        return;
    }
    if(_printState == "lock"){
        emit sendToUIPrintSettingError(7);
        return;
    }else if(_printState != "ready"){
        emit sendToUIPrintSettingError(4);
        return;
    }

    initPrintinfo();

    if(size == 0){
        printStart();
        return;
    }

    fileName = args[0].toString();
    materialName = args[1].toString();

    deletePrintFolder();

    if(size == 2){
        if(unZipFiles(fileName)){
            emit sendToUIPrintSettingError(6);
            return;
        }
        int ret = setupForPrint(materialName);
        if(ret == -6){
            emit sendToUIPrintSettingError(8);
            return;
        }
        if(ret){
            emit sendToUIPrintSettingError(3);
            return;
        }
    }else if(size == 3){
        QJsonObject object = args[2].toJsonObject();
        if(donwloadFiles(object)){
            emit sendToUIPrintSettingError(2);
            return;
        }
        if(unZipFiles(printFilePath + "/" + fileName)){
            emit sendToUIPrintSettingError(6);
            return;
        }

        std::filesystem::path target = printFilePath.toStdString() + "/" + fileName.toStdString();
        std::filesystem::remove(target);

        int ret = setupForPrint(materialName);
        if(ret == -6){
            emit sendToUIPrintSettingError(8);
            return;
        }
        if(ret){
            emit sendToUIPrintSettingError(3);
            return;
        }
    }
    QStringList sl = fileName.split('/').last().split('.');
    sl.removeLast();
    _printName =  sl.join('.');
    _materialName = materialName;

    printStart();
    return;
}

void PrintScheduler::receiveFromUIPrintStateChange(QString CMD)
{
    if(CMD == "pause"){
        _bedWork = BED_PAUSE_WORK;
        _printState = "pauseStart";
        emit sendToUIChangeState("pauseStart");
    }else if(CMD == "resume"){
        if(_bedWork == BED_PAUSE){
            printResume();
            _lastStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
            _enableTimer = true;
            _printState = "print";
            emit sendToUIEnableTimer(true);
            emit sendToUIChangeState("resume");
        }/*else{
            printStart();
        }*/
    }else if(CMD == "finish"){
        bedFinish();
        emit sendToUIChangeState("quit");
    }
    return;
}
void PrintScheduler::receiveFromUIPrintFinishError(){
    bedError();
}

void PrintScheduler::receiveFromUISetHeightOffset(int value)
{
    _printerSetting.heightOffset = value;
    _printerSetting.save();
    return;
}

void PrintScheduler::receiveFromUISetLedOffset(double value)
{
    _printerSetting.ledOffset = value;
    _printerSetting.save();
    return;
}

void PrintScheduler::receiveFromUIGetMaterialList(){
    auto &a = _printerSetting.materialList;
    QVariantList list;
    for(auto& i : a){
        list.push_back(i);
    }
    emit sendToUIMaterialList(list);
    return;
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
    return;
}

int PrintScheduler::receiveFromUIGetHeightOffset()
{
    emit sendToUIHeightOffset(_printerSetting.heightOffset);
    return _printerSetting.heightOffset;
}

double PrintScheduler::receiveFromUIGetLedOffset()
{
    emit sendToUILEDOffset(_printerSetting.ledOffset);
    return _printerSetting.ledOffset;
}

QString PrintScheduler::receiveFromUIGetPrintOption()
{
    QString val = printFilePath + QStringLiteral("/info.json");

    InfoSetting info(val);

    emit sendToUIGetPrintOption(info.serialize());
    return info.serialize();
}

QString PrintScheduler::receiveFromUIGetInfoSetting(QString path)
{
    try {
        QString val;
        miniz_cpp::zip_file file(path.toStdString());
        val = QString::fromStdString(file.read("info.json"));

        emit sendToUIGetInfoSetting(path,val);
        return val;

    } catch (std::exception& e) {
        emit sendToUIGetInfoSetting(path,"");
        return "";
    }
}


void PrintScheduler::receiveFromUIMoveMotor(QString cmd, int micro)
{
    if(cmd == "goHome"){
        bedSerialPort->sendCommand("G02 A-15000 M1");
    }else if(cmd == "autoHome"){
        bedSerialPort->sendCommand("G28 A225");
    }else if(cmd == "moveMaxHeight"){
        char buffer[50] = {0};

        sprintf(buffer,"G01 A%d M0",-(_printerSetting.defaultHeight + _printerSetting.heightOffset));
        bedSerialPort->sendCommand(buffer);
    }else if(cmd == "moveMicro"){
        char buffer[50] = {0};

        sprintf(buffer,"G01 A%d M0",-micro);
        bedSerialPort->sendCommand(buffer);
    }
}

void PrintScheduler::receiveFromUIGetProductInfo()
{
    QJsonObject jo;
    jo.insert("version",Version::getInstance().version);
    jo.insert("modelNo",ModelNo::getInstance().modelNo);
    QJsonDocument doc(jo);
    emit sendToUIProductInfo(doc.toJson());
}

void PrintScheduler::receiveFromUIGetUsbPortError()
{
    if(_printState == "USBCONNECTIONERROR"){
        emit sendToUIPortOpenError(true);
    }else{
        emit sendToUIPortOpenError(false);
    }

}
void PrintScheduler::receiveFromUISetPrintTime(int time)
{
    _printTime = time;
}
