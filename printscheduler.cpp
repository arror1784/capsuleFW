#include "printscheduler.h"


//PrintScheduler* printScheduler = new PrintScheduler();

PrintScheduler::PrintScheduler(/*QMLUImanager* uiManager,DLPServo* dlpServo*/)
//    uiManager(uiManager),
//    dlpServo(dlpServo)
{

}

void PrintScheduler::addPrintingBed(char name){
    BedControl* bedControl = new BedControl(name,bedSerialPort);

    allBed.insert(name,bedControl);
    allBedWork.insert(name,BED_NOT_WORK);
    allBedMoveFinished.insert(name,PRINT_MOVE_NULL);
    allBedPrintImageNum.insert(name,0);
    allBedMaxPrintNum.insert(name,0);

    QObject::connect(this,SIGNAL(sendToBedControl(char,int)),bedControl,SLOT(receiveFromPrintScheduler(char,int)));
    QObject::connect(bedControl,SIGNAL(sendToPrintScheduler(char,int)),this,SLOT(receiveFromBedControl(char,int)));
    QObject::connect(bedSerialPort,SIGNAL(sendSignalToBedControl(char)),bedControl,SLOT(receiveFromBedSerialPort(char)));
//    QObject::connect(bedControl,SIGNAL(sendByteCommand(QByteArray)),bedSerialPort,SLOT(sendByteCommand(QByteArray)));
    QObject::connect(bedControl,SIGNAL(sendCommand(char*)),bedSerialPort,SLOT(sendCommand(char*)));

    QObject::connect(this,SIGNAL(sendToBedControlCommand(char,QString)),bedControl,SLOT(receiveFromPrintSchedulerSendCommand(char,QString)));


    bedControl->setAccleSpeed(bedControl->accelSpeed);
    bedControl->setDecelSpeed(bedControl->decelSpeed);
    bedControl->setMaxSpeed(bedControl->maxSpeed);
    bedControl->setMinSpeed(bedControl->minSpeed);
//    bedControl->transmitCommand("H50 A0 B0 C100");
    emit sendToBedControl(name,SET_LED_BLUE);

    emit sendToQmlSetConfig('A',bedControl->accelSpeed,bedControl->decelSpeed,bedControl->maxSpeed,bedControl->minSpeed,
                            bedControl->bedCuringTime,bedControl->curingTime,bedControl->ZHopHeight);

    sendToBedControlCommand('A',QStringLiteral("H10"));
    bedControl->start();

}

void PrintScheduler::addSerialPort(QString serialPath){

    bedSerialPort = new BedSerialport(serialPath);

    QObject::connect(bedSerialPort,SIGNAL(sendToPrintScheduler(char,int)),this,SLOT(receiveFromSerialPort(char,int)));
    QObject::connect(this,SIGNAL(sendToSerialPortCommand(char*)),bedSerialPort,SLOT(sendCommand(char*)));

}

void PrintScheduler::run(){
    while (1) {
        initBed();
        scheduler();
    }
}

void PrintScheduler::initBed(){

    scheduleLock.lock();
    if(allBedWork['A'] == BED_INIT){
        emit sendToBedControl('A',PRINT_MOVE_AUTOHOME);
        allBedWork['A'] = BED_WORK;
    }else if(allBedWork['A'] == BED_FINISH){
        sendToBedControl('A',PRINT_MOVE_FINISH);
        allBedWork['A'] = BED_FINISH_WORK;
        allBedMoveFinished['A'] = PRINT_MOVE_NULL;
        allBedPrintImageNum['A'] = 0;
    }
    if(allBedWork['B'] == BED_INIT){
        sendToBedControl('B',PRINT_MOVE_INIT);
        allBedWork['B'] = BED_WORK;
    }else if(allBedWork['B'] == BED_FINISH){
        sendToBedControl('B',PRINT_MOVE_FINISH);
        allBedWork['B'] = BED_NOT_WORK;
    }
    if(allBedWork['C'] == BED_INIT){
        sendToBedControl('C',PRINT_MOVE_INIT);
        allBedWork['C'] = BED_WORK;
    }else if(allBedWork['C'] == BED_FINISH){
        sendToBedControl('C',PRINT_MOVE_FINISH);
        allBedWork['C'] = BED_NOT_WORK;
    }
    scheduleLock.unlock();
}
void PrintScheduler::scheduler(){

    scheduleLock.lock();
    if(isDLPWork == false && workingBedCount > 0){
//        qDebug() << "scheduler isDLPWork false" << allBedWork['A'] << allBedMoveFinished['A'];
        isDLPWork = true;
        if(allBedWork['A'] == BED_WORK && allBedMoveFinished['A'] == PRINT_MOVE_LAYER_OK){
            DLPWorked = 'A';
            allBedMoveFinished[DLPWorked] = PRINT_MOVE_READY;
            servoSetPosition(DLPWorked);
            imageChange(DLPWorked);
//            sendToQmlSetVisibleImage(true);
//            emit sendToBedControl(DLPWorked,PRINT_DLP_WORKING);
        }else if(allBedWork['B'] == BED_WORK && allBedMoveFinished['B'] == PRINT_MOVE_LAYER_OK){
            servoSetPosition('B');
            DLPWorked = 'B';
            imageChange(DLPWorked);
            emit sendToBedControl(DLPWorked,PRINT_DLP_WORKING);
        }else if(allBedWork['C'] == BED_WORK && allBedMoveFinished['C'] == PRINT_MOVE_LAYER_OK){
            servoSetPosition('C');
            DLPWorked = 'C';
            imageChange(DLPWorked);
            emit sendToBedControl(DLPWorked,PRINT_DLP_WORKING);
        }
    }
    scheduleLock.unlock();
}
void PrintScheduler::DLPMove(){
//    if(isDLPWork == false && workingBedCount > 0){
//        qDebug()<< "isDLPWork false ";
//        isDLPWork = true;
//        emit sendToBedControl(DLPWorked,PRINT_MOVE_LAYER);

//        switch(DLPWorked){
//        case 'A':
//            if(BBedWork == BED_WORK || BBedMoveFinished == PRINT_MOVE_LAYER_OK){
//                servoSetPosition('B');
//                DLPWorked = 'B';
//            }else if(CBedWork == BED_WORK|| CBedMoveFinished == PRINT_MOVE_LAYER_OK){
//                servoSetPosition('C');
//                DLPWorked = 'C';
//            }else{

//            }
//            break;
//        }
//    }
}
void PrintScheduler::imageChange(char bedChar){
    QString fullPath = allBedPath[bedChar] + "/" +QString::number(allBedPrintImageNum[bedChar]) + ".svg";
    if(allBedPrintImageNum[bedChar] >= allBedMaxPrintNum[bedChar]){
        allBedWork[bedChar] = BED_FINISH;
        workingBedCount--;
        return;
    }else{
        logger->write("print image path : " + fullPath);
        emit sendToQmlChangeImage(fullPath);
    }
    allBedPrintImageNum[bedChar]++;
}
void PrintScheduler::printBed(){

}
void PrintScheduler::receiveFromBedControl(char bedChar,int receive){
    //allBedMoveFinished[bedChar] = receive;
    qDebug() << "scheduler - receiveFromBedControl bed Char : " << bedChar << " receive : " << receive;
    scheduleLock.lock();
    switch (receive) {
        case PRINT_DLP_WORK_FINISH:
            emit sendToQmlSetVisibleImage(false);
            break;
        case PRINT_MOVE_INIT_OK:
        case PRINT_MOVE_LAYER_OK:
            if(allBedWork[bedChar] == BED_PAUSE_WORK){
                emit sendToSerialPortCommand("G02 A-15");
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
            receiveFromQmlBedPrintStart('A');
            break;
    }
    scheduleLock.unlock();
}
void PrintScheduler::receiveFromQmlBedSetBedPath(QChar bedChar,QString path){

    scheduleLock.lock();

    QFile file;
    QString val;
    QDir::setCurrent(path);
    QDir dir(path);
    file.setFileName(QStringLiteral("info.json"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << path + "file open error";
        logger->write(path + "file open error");
    }
    val = file.readAll();

    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject setting = d.object();
    int accel = -1;
    int decel = -1;
    int max = -1;
    int min = -1;
    int bedCuring = -1;
    int curing = -1;
    int zHopHeight = -1;

    if(setting.contains("total_layer")){
        allBedMaxPrintNum[bedChar.cell()] = setting["total_layer"].toInt();
    }
    if(setting.contains("bed_curing_time")){
        allBed[bedChar.cell()]->setBedCuringTime(setting["bed_curing_time"].toInt());
        bedCuring = setting["bed_curing_time"].toInt();
    }
    if(setting.contains("curing_time")){
        allBed[bedChar.cell()]->setCuringTime(setting["curing_time"].toInt());
        curing = setting["curing_time"].toInt();
    }
    if(setting.contains("layer_height")){
        allBed[bedChar.cell()]->setLayerHeightTime(setting["layer_height"].toDouble());
    }
    if(setting.contains("z_hop_height")){
        allBed[bedChar.cell()]->setZHopHeightTime(setting["z_hop_height"].toInt());
        zHopHeight = setting["z_hop_height"].toInt();
    }
    if(setting.contains("move_up_feedrate")){
        allBed[bedChar.cell()]->setMaxSpeed(setting["move_up_feedrate"].toInt());
        max = setting["move_up_feedrate"].toInt();
    }
    if(setting.contains("move_down_feedrate")){
        allBed[bedChar.cell()]->setMinSpeed(setting["move_down_feedrate"].toInt());
        min = setting["move_down_feedrate"].toInt();
    }
    if(setting.contains("accel_speed")){
        allBed[bedChar.cell()]->setAccleSpeed(setting["accel_speed"].toInt());
        accel = setting["accel_speed"].toInt();
    }
    if(setting.contains("decel_speed")){
        allBed[bedChar.cell()]->setDecelSpeed(setting["decel_speed"].toInt());
        decel = setting["decel_speed"].toInt();
    }

    emit sendToQmlSetConfig('A',accel,decel,max,min,bedCuring,curing,zHopHeight);

    if(setting["total_layer"].toInt() < dir.count() - 3)
        logger->write("file error : not enough files");

    allBedPath[bedChar.cell()] = QStringLiteral("file:/") + path;
    scheduleLock.unlock();

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

    allBedWork[bedChar.cell()] = BED_PAUSE_WORK;

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
    sendToQmlSetVisibleImage(true);
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

void PrintScheduler::receiveFromSerialPort(char bedChar,int state){

    char temp[50] = {0};
    if(state == START_FLAG){
        qDebug() << "all Bed Work" << allBedWork['A'];
        switch (allBedWork['A']) {
        case BED_NOT_WORK:
            receiveFromQmlBedPrintStart('A');
            emit sendToSerialPortCommand("H50 A0 B100 C0");
            break;
        case BED_PAUSE:
            sprintf(temp,"G02 %c%lf",'A',allBed['A']->currentPosition);
            emit sendToSerialPortCommand(temp);
            emit sendToSerialPortCommand("H50 A0 B100 C0");
            break;
        case BED_WORK:

            emit sendToSerialPortCommand("H50 A100 B0 C0");
            receiveFromQmlBedPrintPause('A');
            break;
        case BED_INIT:
        case BED_FINISH:
        case BED_PAUSE_WORK:
            break;
        }
    }
}
void PrintScheduler::receiveFromQmlBedPrintRestart(QChar bedChar){
    allBedMoveFinished[bedChar.cell()] = PRINT_MOVE_NULL;
    allBedPrintImageNum[bedChar.cell()] = 0;
    allBedWork[bedChar.cell()] = BED_INIT;
}
