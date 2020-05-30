#include "printscheduler.h"

#include "printsetting.h"
#include "QJsonArray"
//#include <QVariant>
//PrintScheduler* printScheduler = new PrintScheduler();

PrintScheduler::PrintScheduler(){}

void PrintScheduler::addPrintingBed(char name,QString searchPath){
    BedControl* bedControl = new BedControl(name,bedSerialPort);

    bedSerialPort->setReadEnable(false);

    allBed.insert(name,bedControl);
    allBedWork.insert(name,BED_NOT_WORK);
    allBedMoveFinished.insert(name,PRINT_MOVE_NULL);
    allBedPrintImageNum.insert(name,0);
    allBedMaxPrintNum.insert(name,0);
    allBedImageLoaded.insert(name,BED_IMAGE_NONE);
    allBedUSBSearchPath.insert(name,searchPath);

    QObject::connect(this,SIGNAL(sendToBedControl(char,int)),bedControl,SLOT(receiveFromPrintScheduler(char,int)));
    QObject::connect(bedControl,SIGNAL(sendToPrintScheduler(char,int)),this,SLOT(receiveFromBedControl(char,int)));
    QObject::connect(bedSerialPort,SIGNAL(sendSignalToBedControl(char)),bedControl,SLOT(receiveFromBedSerialPort(char)));
//    QObject::connect(bedControl,SIGNAL(sendByteCommand(QByteArray)),bedSerialPort,SLOT(sendByteCommand(QByteArray)));*-
    QObject::connect(bedControl,SIGNAL(sendCommand(QString)),bedSerialPort,SLOT(sendCommand(QString)));

    allBed[name]->setBedCuringTime(PrintSetting::GetInstance()->getPrintSetting("bed_curing_time").toInt());
    allBed[name]->setCuringTime(PrintSetting::GetInstance()->getPrintSetting("curing_time").toInt());
//    qDebug() << "curing_time" << materialSetting["curing_time"].toInt();
    allBed[name]->setZHopHeightTime((int)(PrintSetting::GetInstance()->getPrintSetting("z_hop_height").toInt() * 1000));

    allBed[name]->setMaxSpeed(PrintSetting::GetInstance()->getPrintSetting("max_speed").toInt());
    allBed[name]->setMinSpeed(PrintSetting::GetInstance()->getPrintSetting("init_speed").toInt());

    allBed[name]->setAccleSpeed(PrintSetting::GetInstance()->getPrintSetting("up_accel_speed").toInt(),1);
    allBed[name]->setDecelSpeed(PrintSetting::GetInstance()->getPrintSetting("up_decel_speed").toInt(),1);
    allBed[name]->setAccleSpeed(PrintSetting::GetInstance()->getPrintSetting("down_accel_speed").toInt(),0);
    allBed[name]->setDecelSpeed(PrintSetting::GetInstance()->getPrintSetting("down_decel_speed").toInt(),0);

    allBed[name]->maxSpeed = PrintSetting::GetInstance()->getPrintSetting("max_speed").toInt();
    allBed[name]->minSpeed = PrintSetting::GetInstance()->getPrintSetting("init_speed").toInt();

    allBed[name]->upAccelSpeed = PrintSetting::GetInstance()->getPrintSetting("up_accel_speed").toInt();
    allBed[name]->upDecelSpeed = PrintSetting::GetInstance()->getPrintSetting("up_decel_speed").toInt();
    allBed[name]->downAccelSpeed = PrintSetting::GetInstance()->getPrintSetting("down_accel_speed").toInt();
    allBed[name]->downDecelSpeed = PrintSetting::GetInstance()->getPrintSetting("down_decel_speed").toInt();

    allBed[name]->defaultHeight = PrintSetting::GetInstance()->getPrintSetting("default_height").toInt();

//    QObject::connect(this,SIGNAL(sendToBedControlCommand(char,QString)),bedControl,SLOT(receiveFromPrintSchedulerSendCommand(char,QString)));
    emit sendToSerialPortCommand("H50 A0 B100 C0");

//    sendToBedControlCommand('A',QStringLiteral("H10"));
    emit sendToSerialPortCommand("H10 A0 B100 C0");

    bedSerialPort->setReadEnable(true);

    bedControl->start();
}

int PrintScheduler::addSerialPort(){

//    while(1){
//        sleep(5);
        const auto infos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &info : infos) {

            if(info.portName().contains(QStringLiteral("USB0")) || info.portName().contains(QStringLiteral("ACM"))){

                qDebug() << QObject::tr("Port: ") << info.portName();
                qDebug() << QObject::tr("Vendor Identifier: ") << (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString());
                qDebug() << QObject::tr("Product Identifier: ") << (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString());
                qDebug() << QObject::tr("Busy: ") << (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No"));

                bedSerialPort = new BedSerialport(info.portName());
                QObject::connect(bedSerialPort,SIGNAL(sendToPrintScheduler(char,int)),this,SLOT(receiveFromSerialPort(char,int)));
                QObject::connect(this,SIGNAL(sendToSerialPortCommand(QString)),bedSerialPort,SLOT(sendCommand(QString)));
                return 0;
            }
        }
//    }
    return 1;
}
void PrintScheduler::run(){
    while (1) {
        initBed();
        scheduler();
    }
}

void PrintScheduler::initBed(){

    if(allBedWork['A'] == BED_INIT){
        emit sendToBedControl('A',PRINT_MOVE_AUTOHOME);
        allBedWork['A'] = BED_WORK;
        imageChange('A');
    }else if(allBedWork['A'] == BED_FINISH){
        emit sendToBedControl('A',PRINT_MOVE_FINISH);
        allBedWork['A'] = BED_FINISH_WORK;
        allBedMoveFinished['A'] = PRINT_MOVE_NULL;
        allBedPrintImageNum['A'] = 0;
        emit sendToSerialPortCommand("H50 A100 B0 C0");
        workingBedCount--;
    }else if(allBedWork['A'] == BED_ERROR){
        emit sendToBedControl('A',PRINT_MOVE_FINISH);
        allBedWork['A'] = BED_FINISH_WORK;
        allBedMoveFinished['A'] = PRINT_MOVE_NULL;
        allBedPrintImageNum['A'] = 0;
//        emit sendToQmlPrintFinish();
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        workingBedCount--;
    }
}
void PrintScheduler::scheduler(){

    if(workingBedCount > 0){
//        qDebug() << "scheduler isDLPWork false" << allBedWork['A'] << allBedMoveFinished['A'];
//        sleep(1);
        if(allBedWork['A'] == BED_WORK && allBedMoveFinished['A'] == PRINT_MOVE_LAYER_OK /*&& allBedImageLoaded['A'] == BED_IMAGE_NONE*/){
            DLPWorked = 'A';
            allBedMoveFinished[DLPWorked] = PRINT_MOVE_READY;
            allBedImageLoaded['A'] = BED_IMAGE_NONE;

            if(allBedPrintImageNum['A'] == allBedMaxPrintNum['A']){
                receiveFromQmlBedPrintFinish('A');
            }else if(QFile::exists(printFilePath + "/" +QString::number(allBedPrintImageNum['A']) + ".svg") == false){
                receiveFromQmlBedPrintFinishError('A');
            }else{
                allBedPrintImageNum['A']++;
                emit sendToQmlUpdateProgress(allBedPrintImageNum['A'],allBedMaxPrintNum['A']);
                if(allBedPrintImageNum['A'] <= bedCuringLayer){
                    emit sendToBedControl(DLPWorked,PRINT_MOVE_BEDCURRENT);
                }else{
                    emit sendToBedControl(DLPWorked,PRINT_DLP_WORKING);
                }
            }
        }
    }
}
int PrintScheduler::imageChange(char bedChar){

//    QString fullPath = QStringLiteral("file:/") + allBedPath[bedChar] + "/" + QString::number(allBedPrintImageNum[bedChar]) + ".svg";printFilePath
    QString fullPath = QStringLiteral("file:/") + printFilePath + "/" + QString::number(allBedPrintImageNum[bedChar]) + ".svg";
    Logger::GetInstance()->write("print image path : " + fullPath);
    emit sendToQmlChangeImage(fullPath);

    return 0;
}
void PrintScheduler::receiveFromBedControl(char bedChar,int receive){
    //allBedMoveFinished[bedChar] = receive;
//    qDebug() << "scheduler - receiveFromBedControl bed Char : " << bedChar << " receive : " << receive;
    scheduleLock.lock();
    switch (receive) {
        case PRINT_DLP_WORK_FINISH:
            imageChange(bedChar);
            break;
        case PRINT_MOVE_INIT_OK:
        case PRINT_MOVE_LAYER_OK:
            if(allBedWork[bedChar] == BED_PAUSE_WORK){
                emit sendToQmlPauseFinish();
                allBedWork[bedChar] = BED_PAUSE;
            }
            allBedMoveFinished[bedChar] = PRINT_MOVE_LAYER_OK;
            break;
        case PRINT_MOVE_AUTOHOME_OK:
            break;
        case PRINT_MOVE_FINISH_OK:
            allBedWork[bedChar] = BED_NOT_WORK;
            allBedMoveFinished[bedChar] = PRINT_MOVE_NULL;
            emit sendToSerialPortCommand("H50 A0 B100 C0");
            emit sendToQmlPrintFinish();
            break;
        case PRINT_PAUSE:
            break;
        case PRINT_RESUME:
            break;
    }
    scheduleLock.unlock();
}
void PrintScheduler::receiveFromSerialPort(char bedChar,int state){

    /*if(state == SHORT_BUTTON){
        switch (allBedWork['A']) {
        case BED_NOT_WORK:
            emit sendToSerialPortCommand("H51 A0 B100 C0");
            if( searchBedPrintPath('A') != 0){
                emit sendToSerialPortCommand("H51 A100 B0 C0");
                return;
            }
            if(readyForPrintStart('A',QStringLiteral("custom")) != 0){
                qDebug() << "hello world";
                return;
            }
            receiveFromQmlBedPrintStart(bedChar);
//            receiveFromQmlBedPrint('A');
            emit sendToSerialPortCommand("H50 A0 B0 C100");
            break;
        case BED_PAUSE:
            qDebug() << "print resume";
            receiveFromQmlBedPrintStart('A');
            emit sendToSerialPortCommand("H50 A0 B0 C100");
            break;
        case BED_WORK:
            qDebug() << "print pause";
            receiveFromQmlBedPrintPause('A');
            emit sendToSerialPortCommand("H51 A0 B0 C100");
            break;
        }
    }else if (state == LONG_BUTTON) {
        switch (allBedWork['A']) {
        case BED_NOT_WORK:
            break;
        case BED_WORK:
            break;
        case BED_PAUSE:
            allBedWork['A'] = BED_FINISH;
            break;
        }
    }else */if (state == MOVE_OK) {
        emit sendToQmlMoveOk();
    }
}

int PrintScheduler::readyForPrintStart(char bedChar,QString materialName){

    QFile file;
    QString val;
    QString filePath = allBedPath[bedChar];
    int dirCount = 0;
    int error = 0;

    QJsonDocument d;
    QJsonObject setting;
    QJsonObject materialSetting;

    scheduleLock.lock();
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
        scheduleLock.unlock();
        bedSerialPort->setReadEnable(true);
        return -1;
    }

    file.setFileName(filePath + QStringLiteral("/info.json"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file open error";
        qDebug() << file.fileName();
        Logger::GetInstance()->write(file.fileName() + " file open error");
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        scheduleLock.unlock();
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

    allBed[bedChar]->maxHeight = allBed[bedChar]->defaultHeight + PrintSetting::GetInstance()->getPrintSetting("height_offset").toInt();
    allBed[bedChar]->setLedOffset(PrintSetting::GetInstance()->getPrintSetting("led_offset").toDouble() * 10);

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
        scheduleLock.unlock();
        bedSerialPort->setReadEnable(true);
        qDebug() << error;
        return error;
    }

    allBedMaxPrintNum[bedChar] = setting["total_layer"].toInt();
    allBed[bedChar]->setLayerHeightTime((int)(setting["layer_height"].toDouble() * 1000));

    bedCuringLayer = materialSetting["bed_curing_layer"].toInt();

    allBed[bedChar]->setBedCuringTime(materialSetting["bed_curing_time"].toInt());
    allBed[bedChar]->setCuringTime(materialSetting["curing_time"].toInt());
//    qDebug() << "curing_time" << materialSetting["curing_time"].toInt();
    allBed[bedChar]->setZHopHeightTime((int)(materialSetting["z_hop_height"].toInt() * 1000));

    allBed[bedChar]->setMaxSpeed(materialSetting["max_speed"].toInt());
    allBed[bedChar]->setMinSpeed(materialSetting["init_speed"].toInt());

    allBed[bedChar]->setAccleSpeed(materialSetting["up_accel_speed"].toInt(),1);
    allBed[bedChar]->setDecelSpeed(materialSetting["up_decel_speed"].toInt(),1);
    allBed[bedChar]->setAccleSpeed(materialSetting["down_accel_speed"].toInt(),0);
    allBed[bedChar]->setDecelSpeed(materialSetting["down_decel_speed"].toInt(),0);

    allBed[bedChar]->maxSpeed = materialSetting["max_speed"].toInt();
    allBed[bedChar]->minSpeed = materialSetting["init_speed"].toInt();

    allBed[bedChar]->upAccelSpeed = materialSetting["up_accel_speed"].toInt();
    allBed[bedChar]->upDecelSpeed = materialSetting["up_decel_speed"].toInt();
    allBed[bedChar]->downAccelSpeed = materialSetting["down_accel_speed"].toInt();
    allBed[bedChar]->downDecelSpeed = materialSetting["down_decel_speed"].toInt();
    allBed[bedChar]->layerDelay = materialSetting["layer_delay"].toInt();

    emit sendToQmlSetImageScale(materialSetting["contraction_ratio"].toDouble());


    if(setting.contains("first_accel_speed")){
        allBed[bedChar]->firstAccelSpeed = setting["first_accel_speed"].toInt();
    }else{
        allBed[bedChar]->firstAccelSpeed = setting["down_accel_speed"].toInt();
    }
    if(setting.contains("first_decel_speed")){
        allBed[bedChar]->firstDecelSpeed = setting["first_decel_speed"].toInt();
    }else{
        allBed[bedChar]->firstDecelSpeed = setting["down_decel_speed"].toInt();
    }
    if(setting.contains("first_max_speed")){
        allBed[bedChar]->firstMaxSpeed = setting["first_max_speed"].toInt();
    }else{
        allBed[bedChar]->firstMaxSpeed = setting["max_speed"].toInt();
    }
    if(setting.contains("first_min_speed")){
        allBed[bedChar]->firstMinSpeed = setting["first_min_speed"].toInt();
    }else{
        allBed[bedChar]->firstMinSpeed = setting["init_speed"].toInt();
    }

    if(setting.contains("height_offset")){
        allBed[bedChar]->maxHeight = allBed[bedChar]->defaultHeight + setting["height_offset"].toInt();
        qDebug() << "height_offset_custom" << setting["height_offset"].toInt();
    }
    if(setting.contains("led_offset")){
        allBed[bedChar]->setLedOffset(setting["led_offset"].toDouble() * 10);
        qDebug() << "led_offset_custom" << setting["led_offset"].toInt();
    }


    bedSerialPort->setReadEnable(true);
    scheduleLock.unlock();
    return 0;
}

void PrintScheduler::receiveFromQmlBedPrint(QChar bedChar,QString path,QString materialName){

    char bedName = bedChar.cell();

    allBedPath[bedName] = path;

    int e =0;
    e = readyForPrintStart(bedName,materialName);
    if(e != 0){
        emit sendToQmlPrintError();
        return;
    }
    receiveFromQmlBedPrintStart(bedChar);
}

int PrintScheduler::copySVGPath(QString src, QString dst)
{
    QRegularExpression svgRe("\\d{1,4}.svg");
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

void PrintScheduler::receiveFromQmlBedPrintStart(QChar bedChar){
    if(allBedWork[bedChar.cell()] == BED_PAUSE){
        allBedWork[bedChar.cell()] = BED_WORK;
    }else{
        workingBedCount++;
        allBedMoveFinished[bedChar.cell()] = PRINT_MOVE_NULL;
        allBedPrintImageNum[bedChar.cell()] = 0;
        allBedWork[bedChar.cell()] = BED_INIT;
    }
}
void PrintScheduler::receiveFromQmlBedPrintFinish(QChar bedChar){
    allBedWork[bedChar.cell()] = BED_FINISH;
}
void PrintScheduler::receiveFromQmlBedPrintFinishError(QChar bedChar){
    allBedWork[bedChar.cell()] = BED_ERROR;
}
void PrintScheduler::receiveFromQmlBedPrintPause(QChar bedChar){
    allBedWork[bedChar.cell()] = BED_PAUSE_WORK;
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

void PrintScheduler::receiveFromQmlGoHome(QChar bedChar){
    emit sendToSerialPortCommand("G02 A-15000 M1");
}
void PrintScheduler::receiveFromQmlAutoHome(QChar bedChar){
    emit sendToSerialPortCommand("G28 A225");
}
void PrintScheduler::receiveFromQmlMoveMicro(QChar bedChar,int micro){
    char buffer[50] = {0};

    sprintf(buffer,"G01 %c%d M0",bedChar.cell(),-micro);
    emit sendToSerialPortCommand(buffer);
}
void PrintScheduler::receiveFromQmlMoveMaxHeight(QChar bedChar){
    char buffer[50] = {0};

    sprintf(buffer,"G01 %c%d M0",bedChar.cell(),-(PrintSetting::GetInstance()->getPrintSetting("default_height").toInt() + PrintSetting::GetInstance()->getPrintSetting("height_offset").toInt()));
    emit sendToSerialPortCommand(buffer);
}
