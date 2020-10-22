
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

#include <QDebug>

#include "iostream"
#include "logger.h"
#include "updater.h"
#include "version.h"
#include "printersetting.h"

class WebSocketClient;
class BedControl;
class BedSerialport;
class ResinUpdater;
class PrintScheduler : public QObject
{
    Q_OBJECT
public:
    PrintScheduler(/*QMLUImanager* uiManager,DLPServo* dlpServo*/);

    friend class BedControl;
    friend class ResinUpdater;

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

    void deletePrintFolder();
    int sayHello();

    int donwloadFiles(QJsonObject byte);

    void receiveFromBedControl(int state);
    void receiveFromSerialPort(int state);

    void printStart();
    void printResume();

    void setMotorSpendtime();
    QString materialName() const;

signals:
    void sendToLCDChangeImage(QString imagePath);   //only QML
    void sendToLCDSetImageScale(double value);      //only QML

    void sendToUIUpdateProgress(int progress); //update Progress

    void sendToUIFirstlayerStart();         //For CAL PrintTime
    void sendToUIFirstlayerFinish();        //For CAL PrintTime

    void sendToUIChangeToPrint();       //change ui Ready to Print

//    void sendToUIChangeToPauseStart();             pauseStart      //chage ui print to Pause Start
//    void sendToUIChangeToPauseFinish();            pauseFinish   //change ui Pause Start to Pause Finish
//    void sendToUIChangeToResume();                 resume   //change ui Pause Finish to Print
//    void sendToUIChangeToQuit();                   quit   //change ui all state to Quit

//    void sendToUIChangeToPrintFinish();            printFinish           //chagne UI state Print To Ready
//    void sendToUIChangeToPrintWorkError();         printError //Error when Printing
//    void sendToUIChangeToPrintWorkErrorFinish();   printErrorFinish //change UI State Print To Ready By Error

    void sendToUIChangeState(QString state);

    void sendToUIPrintSettingError(int code);       //print setting Error when received print start from UI

    void sendToUIEnableTimer(bool enable);      //for enabel Timer

    void sendToUIMaterialList(QVariantList name);   //Material List UI must insert Custm resin when resin.json exist

    void sendToUIPrintInfo(QString printerState,QString material, QString fileName,double layerHeight,int elapsedTime,int totalTime,int progress,bool enableTimer);

    void sendToUISetTotalTime(int time); //set realty time

    void sendToUIPortOpenError();

    void sendToUILCDState(bool state);

    void sendToUIExit(bool error);

    void sendToUIMoveOk();                  //only QML

    void MCUFirmwareUpdateFinished();       //only QML

    void sendToUIHeightOffset(int offset);
    void sendToUILEDOffset(double offset);

 //    void sendToUIMaterialOption(QString material,QString option);

    void sendToUIGetPrintOption(QString option);
    void sendToUIGetInfoSetting(QString path,QString option);

    void sendToUIIsCustom(bool value);
//    void sendToUIVersion(QString version);
//    void sendToUIModelNo(QString modelNo);
    void sendToUIProductInfo(QString json);

public slots:

//    void receiveFromQMLPrintStart(QString path,QString materialName);
//    void receiveFromUIPrintStart(QString fileName,QString materialName,QJsonObject byte);
//    void receiveFromUIPrintAgain();

    void receiveFromUIPrintStart(QVariantList args);

    void receiveFromUIPrintStateChange(QString CMD);

    void receiveFromUIGetMaterialList();

    void receiveFromUIGetPrintInfoToWeb();                    // when print time calc finish, send to web info

    int receiveFromUIGetHeightOffset();
    double receiveFromUIGetLedOffset();

//    QString receiveFromUIGetMaterialOption(QString material);

//    QVariant receiveFromUIGetPrintOption(QString key);
//    QVariant receiveFromUIGetPrintOptionFromPath(QString key, QString path);    //from path

    QString receiveFromUIGetPrintOption();
    QString receiveFromUIGetInfoSetting(QString path);

    void receiveFromUISetTotalPrintTime(int time);
    void receiveFromUISetPrintTime(int time);       //for real time
    //use only qml or scheduler

//    void receiveFromUIPrintFinishError();

    void receiveFromUISetHeightOffset(int value);
    void receiveFromUISetLedOffset(double value);

    bool isCustom(QString path);

    void receiveFromUIBusySet(bool bs);
    void receiveFromUIShutdown();

//    void receiveFromUIGoHome();
//    void receiveFromUIAutoHome();
//    void receiveFromUIMoveMaxHeight();
//    void receiveFromUIMoveMicro(int micro);

    void receiveFromUIMoveMotor(QString cmd,int micro);

//    void receiveFromUIGetVersion();
//    void receiveFromUIGetModelNo();
    void receiveFromUIGetProductInfo();

    void receiveFromUpdaterFirmUpdate(QString path);


public:
    BedSerialport* bedSerialPort = nullptr;

private:
    PrinterSetting _printerSetting;
    Version _version;

    BedControl* _bedControl;
    WebSocketClient *_wsClient;

    const QString _fileExtension = ".png";

    QString _bedPath;

    QString _printName;
    QString _materialName;

    QString _portPath;

    QDate _printStartTime;

    int _bedPrintImageNum;
    int _bedWork;
    int _bedMoveFinished;
    int _bedMaxPrintNum;


    int _bedCuringLayer = 5;
    int _progress = 0;
    long long _lastStartTime = 0;
    long long _elapsedTime = 0;
    double _layerHeight = 0.0;
    long long _totalPrintTime = 0;
    QString _printState = "ready";

    int _printTime = 0;

    bool _enableTimer = false;

    bool _bedError = false;

    bool _isBusy;

    bool _LCDState = true;
    bool _USBPortConnection = true;
};

#endif // PRINTSCHEDULER_H
