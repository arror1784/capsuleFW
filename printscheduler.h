
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

#include <QQmlApplicationEngine>

#include <mutex>

#include "iostream"
#include "logger.h"
#include "updater.h"

class WebSocketClient;
class BedControl;
class BedSerialport;
class PrintScheduler : public QThread
{
    Q_OBJECT

public:
    PrintScheduler(/*QMLUImanager* uiManager,DLPServo* dlpServo*/);

    void initBed();
    void bedFinish();
    void bedError();

    void initPrint();

    void printLayer();

    int imageChange();
    void printBed();
    void addPrintingBed(char name/*,QString searchPath*/);
    int addSerialPort();

    int saveFile(QString path,QByteArray byte);

    int copyProject(QString path);
    int copyFilesPath(QString src, QString dst);
    int setupForPrint(QString materialName);
    int unZipFiles(QString path);
    int deletePrintFolder();

    int donwloadFiles(QJsonObject byte);

    void receiveFromBedControl(int state);
    void receiveFromSerialPort(int state);

    void printStart();
    void printResume();

signals:
    void sendToLCDChangeImage(QString imagePath);   //only QML
    void sendToLCDSetImageScale(double value);      //only QML

    void sendToUIUpdateProgress(int progress); //update Progress

    void sendToUIFirstlayerStart();         //For CAL PrintTime
    void sendToUIFirstlayerFinish();        //For CAL PrintTime

    void sendToUIChangeToPrint();       //change ui Ready to Print

    void sendToUIChangeToPauseStart();      //chage ui print to Pause Start
    void sendToUIChangeToPauseFinish();     //change ui Pause Start to Pause Finish
    void sendToUIChangeToResume();          //change ui Pause Finish to Print
    void sendToUIChangeToQuit();            //change ui all state to Quit

    void sendToUIChangeToPrintFinish();             //chagne UI state Print To Ready
    void sendToUIChangeToPrintWorkError();          //Error when Printing
    void sendToUIChangeToPrintWorkErrorFinish();    //change UI State Print To Ready By Error

    void sendToUIPrintSettingError(int code);       //print setting Error when received print start from UI

    void sendToUIEnableTimer(bool enable);      //for enabel Timer

    void sendToUIMaterialList(QVariantList name);   //Material List UI must insert Custm resin when resin.json exist

    void sendToUIPrintInfo(QString printerState,QString material, QString fileName,double layerHeight,int elapsedTime,int totalTime,int progress,bool enableTimer);

    void sendToUISetTotalTime(int time);

    void sendToUIPortOpenError();

    void sendToUILCDState(bool state);

    void sendToUIExitError();               //only QML
    void sendToUIExit();                    //only QML

    void sendToUIMoveOk();                  //only QML

    void MCUFirmwareUpdateFinished();       //only QML

    void sendToUISWUpdateAvailable();       //only QML
    void sendToUISWUpdateNotAvailable();    //only QML
    void sendToUISWUpdateFinished();        //only QML
    void sendToUISWUpdateError();           //only QML

public slots:
    void receiveFromUIConnected();

    void receiveFromQMLPrintStart(QString path,QString materialName);
    void receiveFromUIPrintStart(QString fileName,QString materialName,QJsonObject byte);
    void receiveFromUIPrintAgain();

    void receiveFromUIPrintResume();
    void receiveFromUIPrintPause();
    void receiveFromUIPrintFinish();

    void receiveFromUIGetMaterialList();

    void receiveFromUIGetPrintInfoToWeb();

    QString receiveFromUIGetPrintName(){return _printName;}
    QString receiveFromUIGetMaterialName(){return _materialName;}

    QVariant receiveFromUIGetPrinterOption(QString key);

    QVariant receiveFromUIGetPrintOption(QString key);
    QVariant receiveFromUIGetPrintOptionFromPath(QString key, QString path);    //from path

    void receiveFromUISetTotalPrintTime(int time);
    //use only qml or scheduler

    void receiveFromUIPrintFinishError();

    void receiveFromUISetPrinterOption(QString key,double value);   //only QML
    void receiveFromUISetPrinterOption(QString key,int value);      //only QML
    void receiveFromUISetPrinterOption(QString key,QString value);  //only QML

    QVariant receiveFromUIGetMaterialOptionFromPath(QString path,QString key);
    QVariant receiveFromUIGetMaterialOption(QString material,QString key);

    bool isCustom(QString path);

    void receiveFromUIBusySet(bool bs);
    void receiveFromUIShutdown();

    void receiveFromUIGoHome();
    void receiveFromUIAutoHome();
    void receiveFromUIMoveMicro(int micro);
    void receiveFromUIMoveMaxHeight();

    QString receiveFromUIGetVersion();
    QString receiveFromUIGetModelNo();

    void receiveFromUISetPrintTime(int time);       //for real time

    void receiveFromUpdaterFirmUpdate(QString path);

public:
    BedSerialport* bedSerialPort = nullptr;

    QString materialName() const;

    void setMotorSpendtime();

protected:
    void run()override;

private:
    BedControl* _bedControl;
    WebSocketClient *_wsClient;

    std::mutex _mPrint;

    int bedCuringLayer = 5;

    const QString _fileExtension = ".png";

    QString _bedPath;

    QString _printName;
    QString _materialName;

    QString _portPath;

    int _bedPrintImageNum;
    int _bedWork;
    int _bedMoveFinished;
    int _bedMaxPrintNum;

    int _progress = 0;
    long long _lastStartTime = 0;
    long long _elapsedTime = 0;
    bool _enableTimer = false;
    double _layerHeight = 0.0;
    QString _printState = "ready";
    long long _totalPrintTime = 0;

    int _printTime = 0;

    bool _bedError = false;

    bool _isBusy;

    bool _LCDState = true;
    bool _USBPortConnection = true;
};

#endif // PRINTSCHEDULER_H
