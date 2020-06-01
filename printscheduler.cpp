#include "printscheduler.h"
#include "bedcontrol.h"
#include "bedserialport.h"

#include "printsetting.h"
#include "QJsonArray"
//#include <QVariant>
//PrintScheduler* printScheduler = new PrintScheduler();

PrintScheduler::PrintScheduler(){}

void PrintScheduler::addPrintingBed(char name){
    _bedControl = new BedControl(name,bedSerialPort,this);

    bedSerialPort->setReadEnable(false);
    bedSerialPort->setBedControl(_bedControl);
//    allBed.insert(name,_bedControl);
    _bedWork = BED_NOT_WORK;
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;
    _bedMaxPrintNum = 0;
    _bedImageLoaded = BED_IMAGE_NONE;

//    QObject::connect(_bedControl,SIGNAL(sendToPrintScheduler(char,int)),this,SLOT(receiveFromBedControl(char,int)));
//    QObject::connect(bedSerialPort,SIGNAL(sendSignalToBedControl(char)),_bedControl,SLOT(receiveFromBedSerialPort(char)));
//    QObject::connect(bedControl,SIGNAL(sendByteCommand(QByteArray)),bedSerialPort,SLOT(sendByteCommand(QByteArray)));*-
//    QObject::connect(_bedControl,SIGNAL(sendCommand(QString)),bedSerialPort,SLOT(sendCommand(QString)));

    _bedControl->setBedCuringTime(PrintSetting::GetInstance()->getPrintSetting("bed_curing_time").toInt());
    _bedControl->setCuringTime(PrintSetting::GetInstance()->getPrintSetting("curing_time").toInt());
//    qDebug() << "curing_time" << materialSetting["curing_time"].toInt();
    _bedControl->setZHopHeightTime((int)(PrintSetting::GetInstance()->getPrintSetting("z_hop_height").toInt() * 1000));

    _bedControl->setMaxSpeed(PrintSetting::GetInstance()->getPrintSetting("max_speed").toInt());
    _bedControl->setMinSpeed(PrintSetting::GetInstance()->getPrintSetting("init_speed").toInt());

    _bedControl->setAccleSpeed(PrintSetting::GetInstance()->getPrintSetting("up_accel_speed").toInt(),1);
    _bedControl->setDecelSpeed(PrintSetting::GetInstance()->getPrintSetting("up_decel_speed").toInt(),1);
    _bedControl->setAccleSpeed(PrintSetting::GetInstance()->getPrintSetting("down_accel_speed").toInt(),0);
    _bedControl->setDecelSpeed(PrintSetting::GetInstance()->getPrintSetting("down_decel_speed").toInt(),0);

    _bedControl->maxSpeed = PrintSetting::GetInstance()->getPrintSetting("max_speed").toInt();
    _bedControl->minSpeed = PrintSetting::GetInstance()->getPrintSetting("init_speed").toInt();

    _bedControl->upAccelSpeed = PrintSetting::GetInstance()->getPrintSetting("up_accel_speed").toInt();
    _bedControl->upDecelSpeed = PrintSetting::GetInstance()->getPrintSetting("up_decel_speed").toInt();
    _bedControl->downAccelSpeed = PrintSetting::GetInstance()->getPrintSetting("down_accel_speed").toInt();
    _bedControl->downDecelSpeed = PrintSetting::GetInstance()->getPrintSetting("down_decel_speed").toInt();

    _bedControl->defaultHeight = PrintSetting::GetInstance()->getPrintSetting("default_height").toInt();

    bedSerialPort->sendCommand("H50 A0 B100 C0");

    bedSerialPort->sendCommand("H10 A0 B100 C0");

    bedSerialPort->setReadEnable(true);

//    bedControl->start();
}

int PrintScheduler::addSerialPort(){

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {

        if(info.portName().contains(QStringLiteral("USB0")) /*|| info.portName().contains(QStringLiteral("ACM"))*/){
            bedSerialPort = new BedSerialport(info.portName(),this);
//                QObject::connect(bedSerialPort,SIGNAL(sendToPrintScheduler(char,int)),this,SLOT(receiveFromSerialPort(char,int)));
//                QObject::connect(this,SIGNAL(sendToSerialPortCommand(QString)),bedSerialPort,SLOT(sendCommand(QString)));
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

    while(true)
        QThread::exec();
//    while (1) {
////        scheduler();
////        QApplication::processEvents()
//    }
}

void PrintScheduler::initBed(){
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_AUTOHOME);
    _bedWork = BED_WORK;
    imageChange();
}

void PrintScheduler::bedFinish(){
    emit sendToQmlFinish();
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_FINISH);
    _bedWork = BED_FINISH_WORK;
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;
    emit sendToSerialPortCommand("H50 A100 B0 C0");
}
void PrintScheduler::bedError(){
    _bedControl->receiveFromPrintScheduler(PRINT_MOVE_FINISH);
    _bedWork = BED_FINISH_WORK;
    _bedMoveFinished = PRINT_MOVE_NULL;
    _bedPrintImageNum = 0;
//        emit sendToQmlPrintFinish();
    emit sendToSerialPortCommand("H51 A100 B0 C0");
}

void PrintScheduler::printLayer(){

    if(_bedWork == BED_WORK && _bedMoveFinished == PRINT_MOVE_LAYER_OK){
        _bedMoveFinished = PRINT_MOVE_READY;
        _bedImageLoaded = BED_IMAGE_NONE;

        if(_bedPrintImageNum == _bedMaxPrintNum){
            receiveFromQmlBedPrintFinish();
        }else if(QFile::exists(printFilePath + "/" + QString::number(_bedPrintImageNum) + _fileExtension) == false){
            receiveFromQmlBedPrintFinishError();
        }else{
            _bedPrintImageNum++;
            emit sendToQmlUpdateProgress(_bedPrintImageNum,_bedMaxPrintNum);
            if(_bedPrintImageNum <= bedCuringLayer){
                _bedControl->receiveFromPrintScheduler(PRINT_MOVE_BEDCURRENT);
            }else{
                _bedControl->receiveFromPrintScheduler(PRINT_DLP_WORKING);
            }
        }
    }
}
int PrintScheduler::imageChange(){

//    QString fullPath = QStringLiteral("file:/") + allBedPath[bedChar] + "/" + QString::number(allBedPrintImageNum[bedChar]) + ".svg";printFilePath
    QString fullPath = QStringLiteral("file:/") + printFilePath + "/" + QString::number(_bedPrintImageNum) + _fileExtension;
    Logger::GetInstance()->write("print image path : " + fullPath);

    emit sendToQmlChangeImage(fullPath);

    return 0;
}
void PrintScheduler::receiveFromBedControl(int receive){
    //allBedMoveFinished[bedChar] = receive;
//    qDebug() << "scheduler - receiveFromBedControl bed Char : " << bedChar << " receive : " << receive;
    switch (receive) {
        case PRINT_DLP_WORK_FINISH:
            imageChange();
            break;

        case PRINT_MOVE_INIT_OK:
            emit sendToQmlInit();
        case PRINT_MOVE_LAYER_OK:
            qDebug() << "printLayer";
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
            emit sendToSerialPortCommand("H50 A0 B100 C0");
            emit sendToQmlPrintFinish();
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
    }
}

int PrintScheduler::readyForPrintStart(QString materialName,QString path){

    QFile file;
    QString val;
    QString filePath = path;
    int dirCount = 0;
    int error = 0;

    QJsonDocument d;
    QJsonObject setting;
    QJsonObject materialSetting;

    bedSerialPort->setReadEnable(false);

    if(QDir(printFilePath).exists() == true){
        QDir(printFilePath).removeRecursively();
    }
    if(!QDir().mkdir(printFilePath)){
        qDebug()<< " create folder fail" << printFilePath;
    }else{
        qDebug() << " create folder sucess";
    }
    dirCount = copySVGPath(filePath,printFilePath);
    if(dirCount == -1){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        bedSerialPort->setReadEnable(true);
        return -1;
    }

    file.setFileName(filePath + QStringLiteral("/info.json"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file open error";
        qDebug() << file.fileName();
        Logger::GetInstance()->write(file.fileName() + " file open error");
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        bedSerialPort->setReadEnable(true);
        return -2;
    }else{
        qDebug() << "file open sucess";
        qDebug() << file.fileName();
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
    _bedControl->setLedOffset(PrintSetting::GetInstance()->getPrintSetting("led_offset").toDouble() * 10);

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
    }

    if(setting["total_layer"].toInt() > (dirCount - 1)){
        Logger::GetInstance()->write(QString::number(setting["total_layer"].toInt()));
        Logger::GetInstance()->write(QString::number(dirCount));
        error = -4;
    }
    if(error != 0){
        bedSerialPort->setReadEnable(true);
        qDebug() << error;
        return error;
    }

    _bedMaxPrintNum = setting["total_layer"].toInt();
    _bedControl->setLayerHeightTime((int)(setting["layer_height"].toDouble() * 1000));

    bedCuringLayer = materialSetting["bed_curing_layer"].toInt();

    _bedControl->setBedCuringTime(materialSetting["bed_curing_time"].toInt());
    _bedControl->setCuringTime(materialSetting["curing_time"].toInt());
//    qDebug() << "curing_time" << materialSetting["curing_time"].toInt();
    _bedControl->setZHopHeightTime((int)(materialSetting["z_hop_height"].toInt() * 1000));

    _bedControl->setMaxSpeed(materialSetting["max_speed"].toInt());
    _bedControl->setMinSpeed(materialSetting["init_speed"].toInt());

    _bedControl->setAccleSpeed(materialSetting["up_accel_speed"].toInt(),1);
    _bedControl->setDecelSpeed(materialSetting["up_decel_speed"].toInt(),1);
    _bedControl->setAccleSpeed(materialSetting["down_accel_speed"].toInt(),0);
    _bedControl->setDecelSpeed(materialSetting["down_decel_speed"].toInt(),0);

    _bedControl->maxSpeed = materialSetting["max_speed"].toInt();
    _bedControl->minSpeed = materialSetting["init_speed"].toInt();

    _bedControl->upAccelSpeed = materialSetting["up_accel_speed"].toInt();
    _bedControl->upDecelSpeed = materialSetting["up_decel_speed"].toInt();
    _bedControl->downAccelSpeed = materialSetting["down_accel_speed"].toInt();
    _bedControl->downDecelSpeed = materialSetting["down_decel_speed"].toInt();
    _bedControl->layerDelay = materialSetting["layer_delay"].toInt();

    emit sendToQmlSetImageScale(materialSetting["contraction_ratio"].toDouble());


    if(setting.contains("first_accel_speed")){
        _bedControl->firstAccelSpeed = setting["first_accel_speed"].toInt();
    }else{
        _bedControl->firstAccelSpeed = setting["down_accel_speed"].toInt();
    }
    if(setting.contains("first_decel_speed")){
        _bedControl->firstDecelSpeed = setting["first_decel_speed"].toInt();
    }else{
        _bedControl->firstDecelSpeed = setting["down_decel_speed"].toInt();
    }
    if(setting.contains("first_max_speed")){
        _bedControl->firstMaxSpeed = setting["first_max_speed"].toInt();
    }else{
        _bedControl->firstMaxSpeed = setting["max_speed"].toInt();
    }
    if(setting.contains("first_min_speed")){
        _bedControl->firstMinSpeed = setting["first_min_speed"].toInt();
    }else{
        _bedControl->firstMinSpeed = setting["init_speed"].toInt();
    }

    if(setting.contains("height_offset")){
        _bedControl->maxHeight = _bedControl->defaultHeight + setting["height_offset"].toInt();
        qDebug() << "height_offset_custom" << setting["height_offset"].toInt();
    }
    if(setting.contains("led_offset")){
        _bedControl->setLedOffset(setting["led_offset"].toDouble() * 10);
        qDebug() << "led_offset_custom" << setting["led_offset"].toInt();
    }


    bedSerialPort->setReadEnable(true);
    return 0;
}

void PrintScheduler::receiveFromQmlBedPrint(QString path,QString materialName){

    int e =0;
    e = readyForPrintStart(materialName,path);
    if(e != 0){
        qDebug() << e << path << printFilePath;
        emit sendToQmlPrintError();
        return;
    }
    receiveFromQmlBedPrintStart();
}

int PrintScheduler::copySVGPath(QString src, QString dst)
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
    }
    return count;
}

void PrintScheduler::receiveFromQmlBedPrintStart(){
    if(_bedWork == BED_PAUSE){
        _bedWork = BED_WORK;
        printLayer();
    }else{
        _bedMoveFinished = PRINT_MOVE_NULL;
        _bedPrintImageNum = 0;
        initBed();
    }
}

void PrintScheduler::receiveFromQmlBedPrintFinish(){
    bedFinish();
}
void PrintScheduler::receiveFromQmlBedPrintFinishError(){
    bedError();
}
void PrintScheduler::receiveFromQmlBedPrintPause(){
    _bedWork = BED_PAUSE_WORK;
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
        qDebug() << "file open error";
        qDebug() << file.fileName();
        Logger::GetInstance()->write(file.fileName() + " file open error");
        return -2;
    }else{
        qDebug() << "file open sucess";
        qDebug() << file.fileName();
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
