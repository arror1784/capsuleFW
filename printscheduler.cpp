#include "printscheduler.h"
#include "bedcontrol.h"
#include "bedserialport.h"

#include <QQuickView>
#include <QObject>
#include <QQuickItem>
#include "printsetting.h"
#include "QJsonArray"
#include "QProcess"
#include "websocketclient.h"

PrintScheduler::PrintScheduler(){

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

    _bedControl->setBedCuringTime(PrintSetting::GetInstance()->getPrintSetting("bed_curing_time").toInt());
    _bedControl->setCuringTime(PrintSetting::GetInstance()->getPrintSetting("curing_time").toInt());

    _bedControl->setZHopHeightTime(PrintSetting::GetInstance()->getPrintSetting("z_hop_height").toInt());

    _bedControl->setMaxSpeed(PrintSetting::GetInstance()->getPrintSetting("max_speed").toInt());
    _bedControl->setInitSpeed(PrintSetting::GetInstance()->getPrintSetting("init_speed").toInt());

    _bedControl->setAccleSpeed(PrintSetting::GetInstance()->getPrintSetting("up_accel_speed").toInt(),1);
    _bedControl->setDecelSpeed(PrintSetting::GetInstance()->getPrintSetting("up_decel_speed").toInt(),1);
    _bedControl->setAccleSpeed(PrintSetting::GetInstance()->getPrintSetting("down_accel_speed").toInt(),0);
    _bedControl->setDecelSpeed(PrintSetting::GetInstance()->getPrintSetting("down_decel_speed").toInt(),0);

    _bedControl->defaultHeight = PrintSetting::GetInstance()->getPrintSetting("default_height").toInt();

    bedSerialPort->sendCommand("H10 A0 B100 C0");
}

int PrintScheduler::addSerialPort(){

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {

        if(info.portName().contains(QStringLiteral("USB0")) /*|| info.portName().contains(QStringLiteral("ACM"))*/){
            bedSerialPort = new BedSerialport(info.portName(),this);
            return 0;
        }
    }
    return 1;
}

void PrintScheduler::run(){

    if(addSerialPort())
        return;
    addPrintingBed('A');
//        printScheduler->addPrintingBed("/home/hix/Desktop");
    printFilePath = "/home/pi/printFilePath";
//    printFilePath = "/home/jsh/printFilePath";

    _wsClient = new WebSocketClient(QUrl(QStringLiteral("ws://localhost:8000/ws/printer")));

    _wsClient->open();
    qDebug() << "print scheduler" << QThread::currentThread();
    while(true)
        QThread::exec();
}

void PrintScheduler::initBed(){
    _bedWork = BED_WORK;
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_AUTOHOME);
    imageChange();
}

void PrintScheduler::bedFinish(){

    std::function<void()> func = [this]() {
//        _wsClient->sendFinish();

        _bedWork = BED_FINISH_WORK;
        _bedMoveFinished = PRINT_MOVE_NULL;
        _bedPrintImageNum = 0;

        emit sendToQmlFinish();
        _wsClient->sendSetTimerOnoff(false);
        _bedControl->receiveFromPrintScheduler(PRINT_MOVE_FINISH);

    };
    QMetaObject::invokeMethod(_wsClient,func,Qt::AutoConnection);

}
void PrintScheduler::bedError(){

    std::function<void()> func = [this]() {
//        _wsClient->sendFinish();

        _bedControl->receiveFromPrintScheduler(PRINT_MOVE_FINISH);
        _bedWork = BED_FINISH_WORK;
        _bedMoveFinished = PRINT_MOVE_NULL;
        _bedPrintImageNum = 0;
    //        emit sendToQmlPrintFinish();
        emit sendToQmlFinish();
        _wsClient->sendSetTimerOnoff(false);

    };

    QMetaObject::invokeMethod(_wsClient,func,Qt::AutoConnection);
}

void PrintScheduler::printLayer(){

    if(_bedWork == BED_WORK && _bedMoveFinished == PRINT_MOVE_LAYER_OK){
        _bedMoveFinished = PRINT_MOVE_READY;

        if(_bedPrintImageNum == _bedMaxPrintNum){
            receiveFromQmlBedPrintFinish();
        }else if(QFile::exists(printFilePath + "/" + QString::number(_bedPrintImageNum) + _fileExtension) == false){
            receiveFromQmlBedPrintFinishError();
        }else{
            _bedPrintImageNum++;

            emit sendToQmlUpdateProgress(_bedPrintImageNum,_bedMaxPrintNum);
            _wsClient->sendProgreeUpdate(((double)_bedPrintImageNum/(double)_bedMaxPrintNum) * 100);

            if(_bedPrintImageNum <= bedCuringLayer){
                _bedControl->receiveFromPrintScheduler(PRINT_MOVE_BEDCURRENT);
            }else{
                _bedControl->receiveFromPrintScheduler(PRINT_DLP_WORKING);
            }
        }
    }
}
int PrintScheduler::imageChange(){

    QString fullPath = QStringLiteral("file:/") + printFilePath + "/" + QString::number(_bedPrintImageNum) + _fileExtension;
    Logger::GetInstance()->write("print image path : " + fullPath);

    emit sendToQmlChangeImage(fullPath);

    return 0;
}
void PrintScheduler::receiveFromBedControl(int receive){
    switch (receive) {
        case PRINT_DLP_WORK_FINISH:
            imageChange();
            break;
        case PRINT_MOVE_INIT_OK:
            _wsClient->sendSetTimerOnoff(true);
            _wsClient->sendSetTimerTime();
            emit sendToQmlInit();
        case PRINT_MOVE_LAYER_OK:
            if(_bedWork == BED_PAUSE_WORK){
                emit sendToQmlPauseFinish();
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
            emit sendToQmlPrintFinish();
            _wsClient->sendFinish();
            break;
        case PRINT_PAUSE:
            break;
        case PRINT_RESUME:
            break;
    }
}
void PrintScheduler::receiveFromSerialPort(int state){

    if (state == MOVE_OK) {
        emit sendToQmlMoveOk();
    }else if (state == SHUTDOWN) {
        if(_isBusy)
            emit sendToQmlExitError();
        else
            emit sendToQmlExit();
    }else if(state == LCD_ON){
        emit sendToLCDState(1);
    }else if(state == LCD_OFF){
        emit sendToLCDState(0);
    }
}

void PrintScheduler::receiveFromQmlBusySet(bool bs)
{
    _isBusy = bs;
}

void PrintScheduler::receiveFromQmlShutdown()
{
    bedSerialPort->sendCommand("H200");
    qDebug() << "shutdown";
    QStringList arguments;
    arguments.append("-h");
    arguments.append("now");
    QProcess::execute("shutdown",arguments);
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
        }
    }//    WebSocketClient wsc(QUrl(QStringLiteral("ws://localhost:8000/ws/printer")));

    return count;
}

int PrintScheduler::copyProject(QString path)
{
    QFile file;
    QString val;
    QString filePath = path;
    int dirCount = 0;

    if(QDir(printFilePath).exists() == true){
        QDir(printFilePath).removeRecursively();
    }
    if(!QDir().mkdir(printFilePath)){
        qDebug()<< " create folder fail" << printFilePath;
    }else{
        qDebug() << " create folder sucess";
    }
    dirCount = copyFilesPath(filePath,printFilePath);
    if(dirCount == -1){
        return -1;
    }
    return 0;
}

int PrintScheduler::setupForPrint(QString materialName)
{
    QFile file;
    QString val;
    QString filePath = printFilePath;
    int error = 0;

    QJsonDocument d;
    QJsonObject setting;
    QJsonObject materialSetting;

    QDir dir(filePath);
    dir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );

    file.setFileName(filePath + QStringLiteral("/info.json"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "info file open error";
        Logger::GetInstance()->write(file.fileName() + " file open error");
        return -2;
    }else{
        qDebug() << "info file open sucess";
        Logger::GetInstance()->write(file.fileName() + " file open sucess");
    }
    val = file.readAll();
    file.close();

    d = QJsonDocument::fromJson(val.toUtf8());
    setting = d.object();

    if(materialName == "Custom"){
        materialSetting = setting;
    }else{
        materialSetting = PrintSetting::GetInstance()->getResinSetting(materialName);
    }

    _bedControl->maxHeight = _bedControl->defaultHeight + PrintSetting::GetInstance()->getPrintSetting("height_offset").toInt();

    if(!setting.contains("total_layer")){
        error = -3;
    }else if(!setting.contains("layer_height")){
        error = -3;
    }

    if(!materialSetting.contains("bed_curing_layer")){
        error = -3;
    }else if(!materialSetting.contains("bed_curing_time")){
        error = -3;
    }else if(!materialSetting.contains("curing_time")){
        error = -3;
    }else if(!materialSetting.contains("z_hop_height")){
        error = -3;
    }else if(!materialSetting.contains("max_speed")){
        error = -3;
    }else if(!materialSetting.contains("init_speed")){
        error = -3;
    }else if(!materialSetting.contains("up_accel_speed")){
        error = -3;
    }else if(!materialSetting.contains("up_decel_speed")){
        error = -3;
    }else if(!materialSetting.contains("down_accel_speed")){
        error = -3;
    }else if(!materialSetting.contains("down_decel_speed")){
        error = -3;
    }else if(!materialSetting.contains("contraction_ratio")){
        error = -3;
    }else if(!materialSetting.contains("layer_delay")){
        error = -3;
    }else if(!materialSetting.contains("led_offset")){
        error = -3;
    }

    if(setting["total_layer"].toInt() > (dir.count() - 1)){
        error = -4;
    }

    if(error != 0){
        qDebug() << error;
        return error;
    }

    _bedMaxPrintNum = setting["total_layer"].toInt();
    _bedControl->setLayerHeightTime((int)(setting["layer_height"].toDouble() * 1000));

    bedCuringLayer = materialSetting["bed_curing_layer"].toInt();

    _bedControl->setBedCuringTime(materialSetting["bed_curing_time"].toInt());
    _bedControl->setCuringTime(materialSetting["curing_time"].toInt());

    _bedControl->setZHopHeightTime(materialSetting["z_hop_height"].toInt());

    _bedControl->setMaxSpeed(materialSetting["max_speed"].toInt());
    _bedControl->setInitSpeed(materialSetting["init_speed"].toInt());

    _bedControl->setAccleSpeed(materialSetting["up_accel_speed"].toInt(),1);
    _bedControl->setDecelSpeed(materialSetting["up_decel_speed"].toInt(),1);
    _bedControl->setAccleSpeed(materialSetting["down_accel_speed"].toInt(),0);
    _bedControl->setDecelSpeed(materialSetting["down_decel_speed"].toInt(),0);

    _bedControl->layerDelay = materialSetting["layer_delay"].toInt();

    emit sendToQmlSetImageScale(materialSetting["contraction_ratio"].toDouble());

    double led = (PrintSetting::GetInstance()->getPrintSetting("led_offset").toDouble() / 100) *  materialSetting["led_offset"].toDouble();
    _bedControl->setLedOffset(led * 10);

    return 0;
}

void PrintScheduler::receiveFromQmlBedPrint(QString path,QString materialName){

    //int e =0;
    //e = readyForPrintStart(materialName,path);
    if(copyProject(path)){
        emit sendToQmlPrintError();
        return;
    }
    if(setupForPrint(materialName)){
        emit sendToQmlPrintError();
        return;
    }

    _printName =  path.split('/').last();
    _materialName = materialName;

    receiveFromQmlBedPrintStart();
}

void PrintScheduler::receiveFromQmlBedPrintAgain()
{
    if(setupForPrint(_materialName)){
        emit sendToQmlPrintError();
        return;
    }
    qDebug() << _printName << _materialName;

    receiveFromQmlBedPrintStart();
}

void PrintScheduler::receiveFromQmlBedPrintStart(){

    std::function<void()> func;

    if(_bedWork == BED_PAUSE){
        func = [this]() {
            _wsClient->sendResume();

            _bedWork = BED_WORK;
            printLayer();
        };
    }else{
        func = [this]() {
            _wsClient->sendStart();

            _bedMoveFinished = PRINT_MOVE_NULL;
            _bedPrintImageNum = 0;
            initBed();
        };
    }

    QMetaObject::invokeMethod(_wsClient,func,Qt::AutoConnection);
}

void PrintScheduler::receiveFromQmlBedPrintFinish(){
    bedFinish();
}
void PrintScheduler::receiveFromQmlBedPrintFinishError(){
    bedError();
}
void PrintScheduler::receiveFromQmlBedPrintPause(){

    std::function<void()> func = [this]() {
        _wsClient->sendPause();
        _bedWork = BED_PAUSE_WORK;
    };

    QMetaObject::invokeMethod(_wsClient,func,Qt::AutoConnection);
}
void PrintScheduler::receiveFromQmlUpdateMaterial(){
    QJsonArray a = PrintSetting::GetInstance()->getResinList();
    for (int i = 0;i < a.count();i++) {
        emit sendToQmlInsertMaterialList(a[i].toString());
    }
}
QVariant PrintScheduler::receiveFromQmlGetPrinterOption(QString key){
    return PrintSetting::GetInstance()->getPrintSetting(key).toVariant();
}

void PrintScheduler::receiveFromQmlSetPrinterOption(QString key,double value){
    PrintSetting::GetInstance()->setPrintSetting(key,value);
}
void PrintScheduler::receiveFromQmlSetPrinterOption(QString key,int value){
    PrintSetting::GetInstance()->setPrintSetting(key,value);
}
void PrintScheduler::receiveFromQmlSetPrinterOption(QString key,QString value){
    PrintSetting::GetInstance()->setPrintSetting(key,value);
}

QVariant PrintScheduler::receiveFromQmlGetMaterialOption(QString material,QString key){
    return PrintSetting::GetInstance()->getResinSetting(material)[key].toVariant();
}
QVariant PrintScheduler::receiveFromQmlGetMaterialOptionFromPath(QString path,QString key){

    QFile file;
    QString val;

    file.setFileName(path + QStringLiteral("/info.json"));
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

void PrintScheduler::receiveFromQmlGoHome(){
    bedSerialPort->sendCommand("G02 A-15000 M1");
}
void PrintScheduler::receiveFromQmlAutoHome(){
    bedSerialPort->sendCommand("G28 A225");
}
void PrintScheduler::receiveFromQmlMoveMicro(int micro){
    char buffer[50] = {0};

    sprintf(buffer,"G01 A%d M0",-micro);
    bedSerialPort->sendCommand(buffer);
}
void PrintScheduler::receiveFromQmlMoveMaxHeight(){
    char buffer[50] = {0};

    sprintf(buffer,"G01 A%d M0",-(PrintSetting::GetInstance()->getPrintSetting("default_height").toInt() + PrintSetting::GetInstance()->getPrintSetting("height_offset").toInt()));
    bedSerialPort->sendCommand(buffer);
}
