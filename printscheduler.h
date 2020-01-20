
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
#include <QRegularExpression>
#include <QSerialPort>
#include <QSerialPortInfo>

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

    int imageChange(char bedChar);
    void printBed();
    void addPrintingBed(char name,QString searchPath);
    int addSerialPort();
    int copySVGPath(QString src, QString dst);

signals:
    void sendToBedControl(char bedChar,int receive);
    void sendToQmlChangeImage(QString imagePath);
    void sendToQmlSetVisibleImage(bool visible);

    void sendToQmlPauseFinish();
    void sendToQmlPrintFinish();
    void sendToQmlUpdateProgress(int currentIndex,int maxIndex);

    void sendToSerialPortCommand(QString);

public slots:
    void receiveFromBedControl(char bedChar,int state);
    void receiveFromQmlBedPrintStart(QChar bedChar);
    void receiveFromQmlBedPrintFinish(QChar bedChar);
    void receiveFromQmlBedPrintFinishError(QChar bedChar);
    void receiveFromQmlBedPrintPause(QChar bedChar);
    void receiveFromQmlBedPrint(QChar bedChar,QString path);
    void receiveFromSerialPort(char bedChar,int state);

public:
    int searchBedPrintPath(char bedChar); //search bedPath
    int readyForPrintStart(char bedChar); // info.json

public:
    QMap<char,BedControl*> allBed;
    BedSerialport* bedSerialPort = nullptr;
    QString printFilePath;

private:
    unsigned int isDLPWork = false;
    unsigned int workingBedCount = 0;
    int bedCuringLayer = 5;
    char DLPWorked = 0x00;

    QString printUSBFileName = "capsulePrintFolderTest";

    QMutex scheduleLock;

    QMap<char,QString> allBedPath;
    QMap<char,QString> allBedUSBSearchPath;

    QMap<char,int> allBedPrintImageNum;
    QMap<char,int> allBedImageLoaded;
    QMap<char,int> allBedWork;
    QMap<char,int> allBedMoveFinished;
    QMap<char,int> allBedMaxPrintNum;

};

//extern PrintScheduler* printScheduler;

#endif // PRINTSCHEDULER_H
