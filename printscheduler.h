
#ifndef PRINTSCHEDULER_H
#define PRINTSCHEDULER_H

#include <QObject>
#include <QThread>
#include <QMap>

#include <QVector>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDirIterator>

#include "bedcontrol.h"
#include "bedserialport.h"
#include "iostream"
#include "logger.h"

//#include "dlpprojectercontrol.h"
//#include "qmluimanager.h"
//#include "dlpservo.h"

class PrintScheduler : public QThread
{
    Q_OBJECT

public:
    PrintScheduler(/*QMLUImanager* uiManager,DLPServo* dlpServo*/);
    virtual void run();

    void initBed();

    void scheduler();

    void DLPMove();
    int imageChange(char bedChar);
    void printBed();
    void addPrintingBed(char name);
    void addSerialPort(QString serialPath);


signals:
    void sendToBedControl(char bedChar,int receive);
    char servoGetPosition();
    void servoSetPosition(char bedChar);
    void sendToQmlChangeImage(QString imagePath);
    void sendToQmlSetVisibleImage(bool visible);
    void sendToQmlSetConfig(QChar bedChar,int accel,int decel,int max,int min,int bedCuringTime,int curingTime,int zHopHeight);

    void sendToBedControlCommand(char bedChar,QString command);
    void sendToSerialPortCommand(char*);
    //void getBedState(char bedChar,int* statePtr);

public slots:
    void receiveFromBedControl(char bedChar,int state);
    void receiveFromQmlBedSetBedPath(QChar bedChar,QString path);
    void receiveFromQmlBedPrintStart(QChar bedChar);
    void receiveFromQmlBedPrintFinish(QChar bedChar);
    void receiveFromQmlBedPrintPause(QChar bedChar);
    void receiveFromQmlBedConfig(QChar bedChar,int accel,int decel,int max,int min,int bedCuringTime,int curingTime,int zHopHeight);
    void receiveFromQmlImageLoaded(QChar bedChar);
    void receiveFromQmlSendCommand(QChar bedChar,QString command);
    void receiveFromSerialPort(char bedChar,int state);

public:
    QMap<char,BedControl*> allBed;
    BedSerialport* bedSerialPort = nullptr;
//    QMLUImanager* uiManager = nullptr;
//    DLPServo* dlpServo;
    //DLPProjectercontrol dlpControl;

    int bedState = 9999;

private:
    unsigned int isDLPWork = false;
    unsigned int workingBedCount = 0;
    char DLPWorked = 0x00;

    QMutex scheduleLock;

    QMap<char,QString> allBedPath;
    QMap<char,int> allBedPrintImageNum;
    QMap<char,int> allBedImageLoaded;
    QMap<char,int> allBedWork;
    QMap<char,int> allBedMoveFinished;
    QMap<char,int> allBedMaxPrintNum;

};

//extern PrintScheduler* printScheduler;

#endif // PRINTSCHEDULER_H
