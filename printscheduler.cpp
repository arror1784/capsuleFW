#include "printscheduler.h"

//PrintScheduler* printScheduler = new PrintScheduler();

PrintScheduler::PrintScheduler(/*QMLUImanager* uiManager,DLPServo* dlpServo*/)
//    uiManager(uiManager),
//    dlpServo(dlpServo)
{

}

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
//    QObject::connect(bedControl,SIGNAL(sendByteCommand(QByteArray)),bedSerialPort,SLOT(sendByteCommand(QByteArray)));
    QObject::connect(bedControl,SIGNAL(sendCommand(QString)),bedSerialPort,SLOT(sendCommand(QString)));

    QObject::connect(this,SIGNAL(sendToBedControlCommand(char,QString)),bedControl,SLOT(receiveFromPrintSchedulerSendCommand(char,QString)));


    bedControl->setAccleSpeed(bedControl->accelSpeed,0);
    bedControl->setDecelSpeed(bedControl->decelSpeed,0);
    bedControl->setAccleSpeed(bedControl->accelSpeed,1);
    bedControl->setDecelSpeed(bedControl->decelSpeed,1);
    bedControl->setMaxSpeed(bedControl->maxSpeed);
    bedControl->setMinSpeed(bedControl->minSpeed);

    emit sendToSerialPortCommand("H50 A0 B100 C0");

    emit sendToQmlSetConfig('A',bedControl->accelSpeed,bedControl->decelSpeed,bedControl->maxSpeed,bedControl->minSpeed,
                            bedControl->bedCuringTime,bedControl->curingTime,bedControl->ZHopHeight);

    sendToBedControlCommand('A',QStringLiteral("H10"));

    bedSerialPort->setReadEnable(true);

    bedControl->start();
}

void PrintScheduler::addSerialPort(){

    while(1){
        sleep(5);
        const auto infos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &info : infos) {

            if(info.portName().contains(QStringLiteral("USB0"))/* || info.portName().contains(QStringLiteral("ACM"))*/){

                qDebug() << QObject::tr("Port: ") << info.portName();
                qDebug() << QObject::tr("Vendor Identifier: ") << (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString());
                qDebug() << QObject::tr("Product Identifier: ") << (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString());
                qDebug() << QObject::tr("Busy: ") << (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No"));

                bedSerialPort = new BedSerialport(info.portName());
                QObject::connect(bedSerialPort,SIGNAL(sendToPrintScheduler(char,int)),this,SLOT(receiveFromSerialPort(char,int)));
                QObject::connect(this,SIGNAL(sendToSerialPortCommand(QString)),bedSerialPort,SLOT(sendCommand(QString)));
                return;
            }
        }
    }
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
//                allBedWork['A'] = BED_FINISH;
                receiveFromQmlBedPrintFinish('A');
            }else if(QFile::exists(allBedPath['A'] + "/" +QString::number(allBedPrintImageNum['A']) + ".svg") == false){
//                allBedWork['A'] = BED_ERROR;
                receiveFromQmlBedPrintFinishError('A');
            }else{
                allBedPrintImageNum['A']++;
                if(allBedPrintImageNum['A'] <= bedCuringLayer){
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
    logger->write("print image path : " + fullPath);
    emit sendToQmlChangeImage(fullPath);

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
            break;
        case PRINT_MOVE_AUTOHOME_OK:
            break;
        case PRINT_MOVE_FINISH_OK:
            allBedWork[bedChar] = BED_NOT_WORK;
            allBedMoveFinished[bedChar] = PRINT_MOVE_NULL;
            emit sendToSerialPortCommand("H50 A0 B100 C0");
            break;
        case PRINT_PAUSE:
            break;
        case PRINT_RESUME:
            break;
    }
    scheduleLock.unlock();
}
void PrintScheduler::receiveFromSerialPort(char bedChar,int state){

    if(state == SHORT_BUTTON){
        switch (allBedWork['A']) {
        case BED_NOT_WORK:
            if( receiveFromQmlBedSetBedPath('A') != 0){
                emit sendToSerialPortCommand("H51 A100 B0 C0");
                return;
            }
            receiveFromQmlBedPrintStart('A');
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
    }

}
int PrintScheduler::receiveFromQmlBedSetBedPath(QChar bedChar){

    scheduleLock.lock();

    QFile file;
    QString val;
    QString filePath;
    QDir dir(allBedUSBSearchPath[bedChar.cell()]);
    int dirCount = 0;
    int error = 0;

    bedSerialPort->setReadEnable(false);
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
                scheduleLock.unlock();
                bedSerialPort->setReadEnable(true);
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
        scheduleLock.unlock();
        bedSerialPort->setReadEnable(true);
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
        error = -3;
    }else if(!setting.contains("bed_curing_time")){
        error = -3;
    }else if(!setting.contains("curing_time")){
        error = -3;
    }else if(!setting.contains("layer_height")){
        error = -3;
    }else if(!setting.contains("z_hop_height")){
        error = -3;
    }else if(!setting.contains("move_up_feedrate")){
        error = -3;
    }else if(!setting.contains("move_down_feedrate")){
        error = -3;
    }else if(!setting.contains("up_accel_speed")){
        error = -3;
    }else if(!setting.contains("up_decel_speed")){
        error = -3;
    }else if(!setting.contains("down_accel_speed")){
        error = -3;
    }else if(!setting.contains("down_decel_speed")){
        error = -3;
    }
    if(setting["total_layer"].toInt() > (dirCount - 1)){
        logger->write(QString::number(setting["total_layer"].toInt()));
        logger->write(QString::number(dirCount));      
        error = -4;
    }
    if(error != 0){
        scheduleLock.unlock();
        bedSerialPort->setReadEnable(true);
        return error;
    }

    bedCuringLayer = setting["bed_curing_layer"].toInt();

    allBedMaxPrintNum[bedChar.cell()] = setting["total_layer"].toInt();
    allBed[bedChar.cell()]->setBedCuringTime(setting["bed_curing_time"].toInt());
    allBed[bedChar.cell()]->setCuringTime(setting["curing_time"].toInt());
    allBed[bedChar.cell()]->setLayerHeightTime((int)(setting["layer_height"].toDouble() * 1000));
    allBed[bedChar.cell()]->setZHopHeightTime((int)(setting["z_hop_height"].toInt() * 1000));

    allBed[bedChar.cell()]->setMaxSpeed(setting["move_up_feedrate"].toInt());
    allBed[bedChar.cell()]->setMinSpeed(setting["move_down_feedrate"].toInt());

    allBed[bedChar.cell()]->setAccleSpeed(setting["up_accel_speed"].toInt(),1);
    allBed[bedChar.cell()]->setDecelSpeed(setting["up_decel_speed"].toInt(),1);
    allBed[bedChar.cell()]->setAccleSpeed(setting["down_accel_speed"].toInt(),0);
    allBed[bedChar.cell()]->setDecelSpeed(setting["down_decel_speed"].toInt(),0);

    allBed[bedChar.cell()]->maxSpeed = setting["move_up_feedrate"].toInt();
    allBed[bedChar.cell()]->minSpeed = setting["move_down_feedrate"].toInt();

    allBed[bedChar.cell()]->upAccelSpeed = setting["up_accel_speed"].toInt();
    allBed[bedChar.cell()]->upDecelSpeed = setting["up_decel_speed"].toInt();
    allBed[bedChar.cell()]->downAccelSpeed = setting["down_accel_speed"].toInt();
    allBed[bedChar.cell()]->downDecelSpeed = setting["down_decel_speed"].toInt();



    if(setting.contains("absoule_height")){
        allBed[bedChar.cell()]->maxHeight = setting["absoule_height"].toInt();
    }else if(setting.contains("relative_height")){
        allBed[bedChar.cell()]->maxHeight = allBed[bedChar.cell()]->defaultHeight + setting["relative_height"].toInt();
    }else{
        allBed[bedChar.cell()]->maxHeight = allBed[bedChar.cell()]->defaultHeight;
    }

    if(setting.contains("first_accel_speed")){
        allBed[bedChar.cell()]->firstAccelSpeed = setting["first_accel_speed"].toInt();
    }else{
        allBed[bedChar.cell()]->firstAccelSpeed = setting["down_accel_speed"].toInt();
    }
    if(setting.contains("first_decel_speed")){
        allBed[bedChar.cell()]->firstDecelSpeed = setting["first_decel_speed"].toInt();
    }else{
        allBed[bedChar.cell()]->firstDecelSpeed = setting["down_decel_speed"].toInt();
    }
    if(setting.contains("first_max_speed")){
        allBed[bedChar.cell()]->firstMaxSpeed = setting["first_max_speed"].toInt();
    }else{
        allBed[bedChar.cell()]->firstMaxSpeed = setting["move_up_feedrate"].toInt();
    }
    if(setting.contains("first_min_speed")){
        allBed[bedChar.cell()]->firstMinSpeed = setting["first_min_speed"].toInt();
    }else{
        allBed[bedChar.cell()]->firstMinSpeed = setting["move_down_feedrate"].toInt();
    }

    if(setting.contains("layer_delay")){
        allBed[bedChar.cell()]->layerDelay = setting["layer_delay"].toInt();
    }

    emit sendToSerialPortCommand("H50 A0 B100 C0");
    bedSerialPort->setReadEnable(true);
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
void PrintScheduler::receiveFromQmlBedConfig(QChar bedChar,int accel,int decel,int max,int min,int bedCuringTime,int curingTime,int zHopHeight){
    qDebug() << bedChar << accel << decel << max << min << bedCuringTime << curingTime << zHopHeight;
    if(accel != -1){
        allBed[bedChar.cell()]->setAccleSpeed(accel,0);
    }
    if(decel != -1){
        allBed[bedChar.cell()]->setDecelSpeed(decel,0);
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
void PrintScheduler::receiveFromQmlSendCommand(QChar bedChar,QString command){
    emit sendToBedControlCommand(bedChar.cell(),command);
}
