#include "bedcontrol.h"

#include "bedserialport.h"
#include "printscheduler.h"
#include "printersetting.h"

#include <QtConcurrent/QtConcurrentRun>

#include <QJsonArray>
#include <QJsonObject>

BedControl::BedControl(char bedChar,BedSerialport* bedSerialPort,PrintScheduler *sched) :
    bedChar(bedChar),
    _bedSerialPort(bedSerialPort),
    _sched(sched)
{
}

void BedControl::receiveFromBedSerialPort(){

    switch (bedState) {
    case PRINT_MOVE_UP:
        bedState = PRINT_MOVE_DOWN;
        moveDownCommand();
        break;
    case PRINT_MOVE_DOWN:
        bedState = PRINT_MOVE_READY;
        _sched->receiveFromBedControl(PRINT_MOVE_LAYER_OK );
        break;
    case PRINT_MOVE_INIT:
//            bedState = PRINT_MOVE_PAUSE_WAIT;
         bedState = PRINT_MOVE_READY;
        _sched->receiveFromBedControl(PRINT_MOVE_INIT_OK );
        break;
    case PRINT_MOVE_READY:
        break;
    case PRINT_MOVE_LAYER:
        break;
    case PRINT_MOVE_AUTOHOME:
         bedState = PRINT_MOVE_INIT;
         moveDownCommandMin();
        break;
    case PRINT_MOVE_FINISH:
    case PRINT_CANCLE:
         bedState = PRINT_MOVE_NULL;
         _sched->receiveFromBedControl(PRINT_MOVE_FINISH_OK );
         break;
    default:
        break;
    }
    return;
}

void BedControl::receiveFromPrintScheduler(int receive){

    switch (receive) {
    case PRINT_MOVE_AUTOHOME:
        bedState = PRINT_MOVE_AUTOHOME;
        autoHome();
        break;
    case PRINT_MOVE_INIT:
        bedState = PRINT_MOVE_INIT;
        moveDownCommandMin();
        break;
    case PRINT_MOVE_LAYER:
        break;
    case PRINT_MOVE_FINISH:
        bedState = PRINT_MOVE_FINISH;
        moveUpCommandMax();
        break;
    case PRINT_DLP_WORKING:
        bedState = PRINT_DLP_WORKING;
        printDelay();
        break;
    case PRINT_MOVE_BEDCURRENT:
        bedState = PRINT_MOVE_BEDCURRENT;
        printDelay();
        break;
    case PRINT_CANCLE:
        bedState = PRINT_CANCLE;
        moveUpCommandMax();
        break;
    default:
        break;
    }
    return;
}

int BedControl::UVtime() const
{
    return _UVtime;
}

void BedControl::setUVtime(int UVtime)
{
    _UVtime = UVtime;
}

int BedControl::delayTime() const
{
    return _delayTime;
}

void BedControl::setDelayTime(int delayTime)
{
    _delayTime = delayTime;
}

void BedControl::printDelay(){

    //    _sleepFuture = std::async([this](){
    future = QtConcurrent::run([this](){
        //    qDebug() << "layer delay : " << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");
        QString material = _sched->materialName();
        auto jo = _sched->_printerSetting.UVTimeSpend;
        int time;

        if(jo.contains(material)){
            time = 0;
            jo.insert(material,0);
        }else{
            time = jo[material];
        }
        _delayTime += layerDelay;
        QThread::msleep(layerDelay);

//        qDebug() << "before delay : " << QDateTime::currentDateTime().toString("hh:mm:ss,zzz");
        _bedSerialPort->sendCommand("H11");
        if(bedState == PRINT_MOVE_BEDCURRENT){
            QThread::msleep((unsigned int)bedCuringTime);
        }else if(bedState == PRINT_DLP_WORKING){
            QThread::msleep((unsigned int)curingTime);
        }
        _bedSerialPort->sendCommand("H10");
//        qDebug() << "after delay : " << QDateTime::currentDateTime().toString("hh:mm:ss,zzz");

        if(bedState == PRINT_MOVE_BEDCURRENT){
            jo[material] = time + bedCuringTime;
            _UVtime += bedCuringTime;
        }else if(bedState == PRINT_DLP_WORKING){
            jo[material] = time + curingTime;
            _UVtime += curingTime;
        }

        _sched->_printerSetting.UVTimeSpend = jo;
        _sched->_printerSetting.save();
        moveUpCommand();
    });
}
void BedControl::autoHome(){
//    currentPosition = 0;
    _bedSerialPort->sendCommand("G28 A225");
}
void BedControl::moveUpCommand(){

    char buffer[50] = {0};

    sprintf(buffer,"G01 %c%d M1",bedChar,ZHopHeight);
    _bedSerialPort->sendCommand(buffer);
//    _currentPosition += ZHopHeight;
    _sched->receiveFromBedControl(PRINT_DLP_WORK_FINISH);
    bedState = PRINT_MOVE_UP;
}
void BedControl::moveDownCommand(){
    char buffer[50] = {0};

    sprintf(buffer,"G01 %c%d M0",bedChar,-(ZHopHeight - LayerHeight));
//    _currentPosition += -(ZHopHeight - LayerHeight);
    _bedSerialPort->sendCommand(buffer);
}
void BedControl::moveUpCommandMax(){

//    char buffer[50] = {0};
    _bedSerialPort->sendCommand("G02 A-15000 M1");
//    _currentPosition = -15000;
}
void BedControl::moveDownCommandMin(){
    char buffer[50] = {0};

    sprintf(buffer,"G01 %c%d M0",bedChar,-(maxHeight - LayerHeight));
//    _currentPosition += -(maxHeight - LayerHeight);
    
    _bedSerialPort->sendCommand(buffer);
}
void BedControl::setAccleSpeed(int val,int mode){
    char buffer[50] = {0};
    if(mode){
        _upAccelSpeed = val;
    }else{
        _downAccelSpeed = val;
    }
    sprintf(buffer,"H32 %c%d M%d",bedChar,val,mode);
    _bedSerialPort->sendCommand(buffer);
}
void BedControl::setDecelSpeed(int val,int mode){
    char buffer[50] = {0};
    if(mode){
        _upDecelSpeed = val;
    }else{
        _downDecelSpeed = val;
    }
    sprintf(buffer,"H33 %c%d M%d",bedChar,val,mode);
    _bedSerialPort->sendCommand(buffer);
}

void BedControl::setMaxSpeed(int val){
    char buffer[50] = {0};
    _maxSpeed = val;
    sprintf(buffer,"H30 %c%d",bedChar,val);
    _bedSerialPort->sendCommand(buffer);
}
void BedControl::setInitSpeed(int val){
    char buffer[50] = {0};
    _InitSpeed = val;
    sprintf(buffer,"H31 %c%d",bedChar,val);
    _bedSerialPort->sendCommand(buffer);
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
    _bedSerialPort->sendCommand(buffer);
}
