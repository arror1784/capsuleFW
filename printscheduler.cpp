#include "printscheduler.h"
 #include <QStorageInfo>

//PrintScheduler* printScheduler = new PrintScheduler();

PrintScheduler::PrintScheduler(/*QMLUImanager* uiManager,DLPServo* dlpServo*/)
//    uiManager(uiManager),
//    dlpServo(dlpServo)
{

}

void PrintScheduler::addPrintingBed(char name,QString searchPath){
    BedControl* bedControl = new BedControl(name,bedSerialPort);

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
//    QObject::connect(bedControl,SIGNAL(sendByteCommand(QByteArray)),bedSerialPort,SLOT(sendByteCommand(QByteArray)));
    QObject::connect(bedControl,SIGNAL(sendCommand(QString)),bedSerialPort,SLOT(sendCommand(QString)));

    QObject::connect(this,SIGNAL(sendToBedControlCommand(char,QString)),bedControl,SLOT(receiveFromPrintSchedulerSendCommand(char,QString)));


    bedControl->setAccleSpeed(bedControl->accelSpeed);
    bedControl->setDecelSpeed(bedControl->decelSpeed);
    bedControl->setMaxSpeed(bedControl->maxSpeed);
    bedControl->setMinSpeed(bedControl->minSpeed);

    emit sendToSerialPortCommand("H50 A0 B0 C100");

    emit sendToQmlSetConfig('A',bedControl->accelSpeed,bedControl->decelSpeed,bedControl->maxSpeed,bedControl->minSpeed,
                            bedControl->bedCuringTime,bedControl->curingTime,bedControl->ZHopHeight);

    sendToBedControlCommand('A',QStringLiteral("H10"));
    bedControl->start();

}

void PrintScheduler::addSerialPort(QString serialPath){

    bedSerialPort = new BedSerialport(serialPath);
    bedSerialPort->m_serialPort->readAll();

    QObject::connect(bedSerialPort,SIGNAL(sendToPrintScheduler(char,int)),this,SLOT(receiveFromSerialPort(char,int)));
    QObject::connect(this,SIGNAL(sendToSerialPortCommand(QString)),bedSerialPort,SLOT(sendCommand(QString)));

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
    }
}
void PrintScheduler::scheduler(){

    if(isDLPWork == false && workingBedCount > 0){
//        qDebug() << "scheduler isDLPWork false" << allBedWork['A'] << allBedMoveFinished['A'];
        isDLPWork = true;
        if(allBedWork['A'] == BED_WORK && allBedMoveFinished['A'] == PRINT_MOVE_LAYER_OK && allBedImageLoaded['A'] == BED_IMAGE_NONE){
            DLPWorked = 'A';
            allBedMoveFinished[DLPWorked] = PRINT_MOVE_READY;
            allBedImageLoaded['A'] = BED_IMAGE_NONE;

            if(allBedPrintImageNum['A'] > allBedMaxPrintNum['A']){
                allBedWork['A'] = BED_FINISH;
                workingBedCount--;
            }else if(QFile::exists(allBedPath['A'] + "/" +QString::number(allBedPrintImageNum['A']) + ".svg") == false){
                allBedWork['A'] = BED_FINISH;
                workingBedCount--;
                emit sendToSerialPortCommand("H50 A100 B0 C0");
            }else{
                emit sendToQmlSetVisibleImage(true);
                allBedPrintImageNum['A']++;
                if(allBedPrintImageNum['A'] < 5){
                    emit sendToBedControl(DLPWorked,PRINT_MOVE_BEDCURRENT);
                }else{
                    emit sendToBedControl(DLPWorked,PRINT_DLP_WORKING);
                }
            }
//            imageChange(DLPWorked);
//            emit sendToBedControl(DLPWorked,PRINT_DLP_WORKING);
        }
    }
}
int PrintScheduler::imageChange(char bedChar){
    QString fullPath = QStringLiteral("file:/") + allBedPath[bedChar] + "/" + QString::number(allBedPrintImageNum[bedChar]) + ".svg";

//    bool dstFilexist=QFile::exists(allBedPath[bedChar] + "/" +QString::number(allBedPrintImageNum[bedChar]) + ".svg");
//    if(dstFilexist == false){
//        allBedWork[bedChar] = BED_FINISH;
//        workingBedCount--;
//        return -1;
//    }
//    if(allBedPrintImageNum[bedChar] >= allBedMaxPrintNum[bedChar]){
//        allBedWork[bedChar] = BED_FINISH;
//        workingBedCount--;
//        return 1;
//    }else{
        logger->write("print image path : " + fullPath);
        emit sendToQmlChangeImage(fullPath);
//    }
//    allBedPrintImageNum[bedChar]++;
    return 0;
}
void PrintScheduler::receiveFromBedControl(char bedChar,int receive){
    //allBedMoveFinished[bedChar] = receive;
//    qDebug() << "scheduler - receiveFromBedControl bed Char : " << bedChar << " receive : " << receive;
    scheduleLock.lock();
    switch (receive) {
        case PRINT_DLP_WORK_FINISH:
//            emit sendToQmlSetVisibleImage(false);
            imageChange(bedChar);
            break;
        case PRINT_MOVE_INIT_OK:
        case PRINT_MOVE_LAYER_OK:
            if(allBedWork[bedChar] == BED_PAUSE_WORK){
                allBedWork[bedChar] = BED_PAUSE;
            }
            allBedMoveFinished[bedChar] = PRINT_MOVE_LAYER_OK;
            isDLPWork = false;
            break;
        case PRINT_MOVE_AUTOHOME_OK:
            break;
        case PRINT_MOVE_FINISH_OK:
            allBedWork[bedChar] = BED_NOT_WORK;
            emit sendToSerialPortCommand("H50 A0 B0 C100");
            break;
        case PRINT_PAUSE:
            break;
        case PRINT_RESUME:
            break;
//        case IMAGE_CHANGE:
//            imageChange(bedChar);
//            break;
    }
    scheduleLock.unlock();
}
void PrintScheduler::receiveFromSerialPort(char bedChar,int state){

    char temp[50] = {0};
    if(state == SHORT_BUTTON){
//        qDebug() << "all Bed Work" << allBedWork['A'];
        switch (allBedWork['A']) {
        case BED_NOT_WORK:
            receiveFromQmlBedSetBedPath('A');
            receiveFromQmlBedPrintStart('A');
            emit sendToSerialPortCommand("H50 A0 B0 C100");
            break;
        case BED_PAUSE:
            qDebug() << "print resume";
            receiveFromQmlBedPrintStart('A');
            emit sendToSerialPortCommand("H50 A0 B0 C100");
            break;
        case BED_WORK:
            emit sendToSerialPortCommand("H51 A0 B0 C100");
            receiveFromQmlBedPrintPause('A');
            allBedWork[bedChar] = BED_PAUSE_WORK;
            qDebug() << "print pause";
            break;
        }
    }else if (state == LONG_BUTTON) {
        switch (allBedWork['A']) {
        case BED_NOT_WORK:

            break;
        case BED_PAUSE:
            qDebug() << "print resume";
            emit sendToBedControl('A',PRINT_CANCLE);
            allBedWork[bedChar] = BED_NOT_WORK;
            allBedMoveFinished[bedChar] = PRINT_MOVE_NULL;
            allBedPrintImageNum[bedChar] = 0;
            break;
        }
    }
}
int PrintScheduler::receiveFromQmlBedSetBedPath(QChar bedChar){

    scheduleLock.lock();

    QFile file;
    QString val;
    QString filePath;
    QDir dir(allBedUSBSearchPath[bedChar.cell()]);
    int dirCount = 0;

    emit sendToSerialPortCommand("H51 A0 B100 C0");

    if(QDir(printFilePath).exists() == true){
        QDir(printFilePath).removeRecursively();
    }

    QDir().mkdir(printFilePath);

    QDirIterator it(allBedUSBSearchPath[bedChar.cell()], QDirIterator::Subdirectories|QDirIterator::FollowSymlinks);
    while(it.hasNext())
    {
        it.next();
//            logger->write(it.fileInfo().absolutePath());
        if(it.fileInfo().absolutePath().endsWith(printUSBFileName)){
            logger->write("fooooound!!!!!");
            qDebug() << "foooooooooooound";
            qDebug() << it.fileInfo().absolutePath();
            filePath = it.fileInfo().absolutePath();
            logger->write(filePath);

            dirCount = copySVGPath(filePath,printFilePath);
            if(dirCount == -1){
                emit sendToSerialPortCommand("H51 A100 B0 C0");
                return -1;
            }
            break;
        }
    }

    allBedPath[bedChar.cell()] = printFilePath;
    qDebug() << filePath;

    file.setFileName(filePath + QStringLiteral("/info.json"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file open error";
        qDebug() << file.fileName();
        logger->write(file.fileName() + " file open error");
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -2;
    }else{
        qDebug() << "file open sucess";
        qDebug() << file.fileName();
        logger->write(file.fileName() + " file open sucess");
    }
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject setting = d.object();

    if(!setting.contains("total_layer")){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -3;
    }else if(!setting.contains("bed_curing_time")){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -3;
    }else if(!setting.contains("curing_time")){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -3;
    }else if(!setting.contains("layer_height")){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -3;
    }else if(!setting.contains("z_hop_height")){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -3;
    }else if(!setting.contains("move_up_feedrate")){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -3;
    }else if(!setting.contains("move_down_feedrate")){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -3;
    }

    if(setting["total_layer"].toInt() != dirCount){
        emit sendToSerialPortCommand("H51 A100 B0 C0");
        return -4;
    }

    allBedMaxPrintNum[bedChar.cell()] = setting["total_layer"].toInt();
    allBed[bedChar.cell()]->setBedCuringTime(setting["bed_curing_time"].toInt());
    allBed[bedChar.cell()]->setCuringTime(setting["curing_time"].toInt());
    allBed[bedChar.cell()]->setLayerHeightTime((int)(setting["layer_height"].toDouble() * 1000));
    allBed[bedChar.cell()]->setZHopHeightTime((int)(setting["z_hop_height"].toInt() * 1000));

    allBed[bedChar.cell()]->setMaxSpeed(setting["move_up_feedrate"].toInt());
    allBed[bedChar.cell()]->setMinSpeed(setting["move_down_feedrate"].toInt());

//    if(setting.contains("accel_speed")){
//        allBed[bedChar.cell()]->setAccleSpeed(setting["accel_speed"].toInt());
//    }
//    if(setting.contains("decel_speed")){
//        allBed[bedChar.cell()]->setDecelSpeed(setting["decel_speed"].toInt());
//    }

    if(setting.contains("up_accel_speed")){
        allBed[bedChar.cell()]->setUpAccleSpeed(setting["up_accel_speed"].toInt());
    }
    if(setting.contains("up_decel_speed")){
        allBed[bedChar.cell()]->setUpDecelSpeed(setting["up_decel_speed"].toInt());
    }
    if(setting.contains("down_accel_speed")){
        allBed[bedChar.cell()]->setDownAccleSpeed(setting["down_accel_speed"].toInt());
    }
    if(setting.contains("down_decel_speed")){
        allBed[bedChar.cell()]->setDownDecelSpeed(setting["down_decel_speed"].toInt());
    }

    qDebug() << "hello world";
    emit sendToSerialPortCommand("H50 A0 B100 C0");

    scheduleLock.unlock();
    return 0;
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
        }
    }
    return count;
}
void PrintScheduler::receiveFromQmlBedPrintStart(QChar bedChar){
    if(allBedWork[bedChar.cell()] == BED_PAUSE){
        allBedWork[bedChar.cell()] = BED_WORK;
        isDLPWork = false;
    }else{
        workingBedCount++;
        allBedMoveFinished[bedChar.cell()] = PRINT_MOVE_NULL;
        allBedPrintImageNum[bedChar.cell()] = 0;
        allBedWork[bedChar.cell()] = BED_INIT;
    }
}
void PrintScheduler::receiveFromQmlBedPrintFinish(QChar bedChar){
    allBedWork[bedChar.cell()] = BED_FINISH;
    workingBedCount--;
}
void PrintScheduler::receiveFromQmlBedPrintPause(QChar bedChar){

    allBedWork[bedChar.cell()] = BED_PAUSE;

}
void PrintScheduler::receiveFromQmlBedConfig(QChar bedChar,int accel,int decel,int max,int min,int bedCuringTime,int curingTime,int zHopHeight){
    qDebug() << bedChar << accel << decel << max << min << bedCuringTime << curingTime << zHopHeight;
    if(accel != -1){
        allBed[bedChar.cell()]->setAccleSpeed(accel);
    }
    if(decel != -1){
        allBed[bedChar.cell()]->setDecelSpeed(decel);
    }
    if(max != -1){
        allBed[bedChar.cell()]->setMaxSpeed(max);
    }
    if(min != -1){
        allBed[bedChar.cell()]->setMinSpeed(min);
    }
    if(bedCuringTime != -1){
        allBed[bedChar.cell()]->setBedCuringTime(bedCuringTime);
    }
    if(curingTime != -1){
        allBed[bedChar.cell()]->setCuringTime(curingTime);
    }
    if(zHopHeight != -1){
        allBed[bedChar.cell()]->setZHopHeightTime(zHopHeight);
    }
}
void PrintScheduler::receiveFromQmlImageLoaded(QChar bedChar){
//    qDebug() << bedChar;
//    sendToQmlSetVisibleImage(true);
    logger->write("image loaded");
    if(allBedPrintImageNum[bedChar.cell()] < 5){
        emit sendToBedControl(DLPWorked,PRINT_MOVE_BEDCURRENT);
    }else{
        emit sendToBedControl(DLPWorked,PRINT_DLP_WORKING);
    }
    return;
}
void PrintScheduler::receiveFromQmlSendCommand(QChar bedChar,QString command){
    emit sendToBedControlCommand(bedChar.cell(),command);
}
