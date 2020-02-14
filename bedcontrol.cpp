#include "bedcontrol.h"

BedControl::BedControl(char bedChar,BedSerialport* bedSerialPort) :
    bedChar(bedChar),
    bedSerialPort(bedSerialPort)
{
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
}

void BedControl::handleTimeout(){
    emit sendToPrintScheduler(bedChar,PRINT_DLP_WORK_FINISH);
    bedState = PRINT_DLP_NOT_WORKING;
}

void BedControl::run(){
    while(1){
        bedControlLock.lock();
        if(current_function != nullptr)
            (this->*(current_function))();
        bedControlLock.unlock();
    }
}

void BedControl::getBedState(char bedChar,int* statePtr){
    if(bedChar == this->bedChar){
       *statePtr = bedState;
    }
}

void BedControl::receiveFromBedSerialPort(char bedChar){
//    qDebug() << "bedControl - receiveFromSerialPort bed Char : " << bedChar << " bedState :" << bedState;
    if(bedChar == this->bedChar){
         switch (bedState) {
        case PRINT_MOVE_UP:
            bedState = PRINT_MOVE_DOWN;
            current_function = &BedControl::moveDownCommand;
            break;
        case PRINT_MOVE_DOWN:
            bedState = PRINT_MOVE_READY;
             emit sendToPrintScheduler(bedChar, PRINT_MOVE_LAYER_OK );
            break;
        case PRINT_MOVE_INIT:
//            bedState = PRINT_MOVE_PAUSE_WAIT;
             bedState = PRINT_MOVE_READY;
            emit sendToPrintScheduler(bedChar, PRINT_MOVE_INIT_OK );
            break;

        case PRINT_MOVE_READY:
            break;
        case PRINT_MOVE_LAYER:
            break;
        case PRINT_MOVE_AUTOHOME:
             bedState = PRINT_MOVE_INIT;
             current_function = &BedControl::moveDownCommandMin;
            break;
        case PRINT_MOVE_FINISH:
        case PRINT_CANCLE:
             bedState = PRINT_MOVE_NULL;
             emit sendToPrintScheduler(bedChar,PRINT_MOVE_FINISH_OK );
             break;
        default:
            break;
        }
//        start();
    }
    return;
}

void BedControl::receiveFromPrintScheduler(char bedChar,int receive){

//    qDebug()  <<"bedControl - receiveFromScheduler bed Char :" << bedChar << " receive : " << receive;
    if(bedChar == this->bedChar){
        switch (receive) {
        case PRINT_MOVE_AUTOHOME:
            bedState = PRINT_MOVE_AUTOHOME;
            current_function = &BedControl::autoHome;
            break;
        case PRINT_MOVE_INIT:
            bedState = PRINT_MOVE_INIT;
            current_function = &BedControl::moveDownCommandMin;
            break;
        case PRINT_MOVE_LAYER:
            break;
        case PRINT_MOVE_FINISH:
            bedState = PRINT_MOVE_FINISH;
            current_function = &BedControl::moveUpCommandMax;
            break;
        case PRINT_DLP_WORKING:
            bedState = PRINT_DLP_WORKING;
            current_function = &BedControl::printDelay;
            break;
        case PRINT_MOVE_BEDCURRENT:
            bedState = PRINT_MOVE_BEDCURRENT;
            current_function = &BedControl::printDelay;
            break;
        case PRINT_CANCLE:
            bedState = PRINT_CANCLE;
            current_function = &BedControl::moveUpCommandMax;
            break;
        default:
            break;
        }
    }
    return;
}

void BedControl::printDelay(){

    qDebug() << "layer delay : " << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");
    msleep(layerDelay);
    qDebug() << "before delay : " << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");
    emit sendCommand("H11");
    if(bedState == PRINT_MOVE_BEDCURRENT){
        msleep(bedCuringTime);
    }else if(bedState == PRINT_DLP_WORKING){
        msleep(curingTime);
    }
    emit sendCommand("H10");
    qDebug() << "after delay : " << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");
    current_function = &BedControl::moveUpCommand;
}
void BedControl::autoHome(){

//    currentPosition = 0;
    emit sendCommand("G28 A225");
    current_function = nullptr;
}
void BedControl::moveUpCommand(){

    char buffer[50] = {0};

    sprintf(buffer,"G01 %c%d M1",bedChar,ZHopHeight);
    emit sendCommand(buffer);
//    currentPosition += ZHopHeight;
    emit sendToPrintScheduler(bedChar,PRINT_DLP_WORK_FINISH);
    bedState = PRINT_MOVE_UP;

    current_function = nullptr;
}
void BedControl::moveDownCommand(){
    char buffer[50] = {0};
//    sprintf(buffer,"H32 %c%d",bedChar,downAccelSpeed);
//    emit sendCommand(buffer);
//    sprintf(buffer,"H33 %c%d",bedChar,downDecelSpeed);
//    emit sendCommand(buffer);
    sprintf(buffer,"G01 %c%d M0",bedChar,-(ZHopHeight - LayerHeight));
    emit sendCommand(buffer);
//    currentPosition += -(ZHopHeight - LayerHeight);
    current_function = nullptr;
}
void BedControl::moveUpCommandMax(){

    char buffer[50] = {0};

//    sprintf(buffer,"H32 %c%d",bedChar,upAccelSpeed);
//    emit sendCommand(buffer);
//    sprintf(buffer,"H33 %c%d",bedChar,upDecelSpeed);
//    emit sendCommand(buffer);

    emit sendCommand("G02 A-15000 M1");
//    currentPosition = -15;
    current_function = nullptr;
}
void BedControl::moveDownCommandMin(){
    char buffer[50] = {0};

//    sprintf(buffer,"H32 %c%d",bedChar,downAccelSpeed);
//    emit sendCommand(buffer);
//    sprintf(buffer,"H33 %c%d",bedChar,downDecelSpeed);
//    emit sendCommand(buffer);
    setAccleSpeed(firstAccelSpeed,0);
    setDecelSpeed(firstDecelSpeed,0);
    setMaxSpeed(firstMaxSpeed);
    setMinSpeed(firstMinSpeed);

    sprintf(buffer,"G01 %c%d M0",bedChar,-(maxHeight - LayerHeight));
    emit sendCommand(buffer);
//    currentPosition += -(maxHeight - LayerHeight);

    setAccleSpeed(downAccelSpeed,0);
    setDecelSpeed(downDecelSpeed,0);
    setMaxSpeed(maxSpeed);
    setMinSpeed(minSpeed);

    current_function = nullptr;
}
void BedControl::setAccleSpeed(int val,int mode){
    char buffer[50] = {0};
    sprintf(buffer,"H32 %c%d M%d",bedChar,val,mode);
    emit sendCommand(buffer);
}
void BedControl::setDecelSpeed(int val,int mode){
    char buffer[50] = {0};
    sprintf(buffer,"H33 %c%d M%d",bedChar,val,mode);
    emit sendCommand(buffer);
}
//void BedControl::setUpAccleSpeed(int val){
//    char buffer[50] = {0};
//    sprintf(buffer,"H31 %c%d",bedChar,val);
//    emit sendCommand(buffer);
//    upAccelSpeed = val;
//}
//void BedControl::setUpDecelSpeed(int val){
//    upDecelSpeed = val;
//}
//void BedControl::setDownAccleSpeed(int val){
//    downAccelSpeed = val;
//}
//void BedControl::setDownDecelSpeed(int val){
//    downDecelSpeed = val;
//}
void BedControl::setMaxSpeed(int val){
    char buffer[50] = {0};
    sprintf(buffer,"H30 %c%d",bedChar,val);
    emit sendCommand(buffer);
}
void BedControl::setMinSpeed(int val){
    char buffer[50] = {0};
    sprintf(buffer,"H31 %c%d",bedChar,val);
    emit sendCommand(buffer);
}

void BedControl::setCuringTime(const int value){
    this->curingTime = value;
}
void BedControl::setBedCuringTime(const int value){
    this->bedCuringTime = value;
}
void BedControl::setZHopHeightTime(const int value){
    this->ZHopHeight = value;
}
void BedControl::setLayerHeightTime(const int value){
    this->LayerHeight = value;
}
void BedControl::setLedOffset(int value){

    char buffer[50] = {0};
    this->ledOffset=value;
    sprintf(buffer,"H12 %c%d",bedChar,value);
    emit sendCommand(buffer);

}


