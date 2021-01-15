
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
    void initPrintinfo();

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

    int donwloadFiles(QJsonObject& byte);

    void receiveFromBedControl(int state);
    void receiveFromSerialPort(int state);

    void printStart();
    void printResume();

    void setMotorSpendtime();
    QString materialName() const;

    void setTotaltime(uint64_t moveTime);

    void sendAutoReboot(bool value);

signals:
    void sendToLCDChangeImage(QString imagePath);   //only QML
    void sendToLCDSetImageScale(double value);      //only QML

    void sendToUIUpdateProgress(int progress); //update Progress

    void sendToUIChangeToPrint();       //change ui Ready to Print

    void sendToUIChangeState(QString state);

    void sendToUIPrintSettingError(int code);       //print setting Error when received print start from UI

    void sendToUIEnableTimer(bool enable);      //for enabel Timer

    void sendToUIMaterialList(QVariantList name);   //Material List UI must insert Custm resin when resin.json exist

    void sendToUIPrintInfo(QString printerState,QString material, QString fileName,double layerHeight,int elapsedTime,int totalTime,int progress,bool enableTimer);

    void sendToUISetTotalTime(int time); //set realty time

    void sendToUIPortOpenError(bool error);

    void sendToUILCDState(bool state);

    void sendToUIExit(bool error);

    void sendToUIMoveOk();                  //only QML

    void MCUFirmwareUpdateFinished();       //only QML

    void sendToUIHeightOffset(int offset);
    void sendToUILEDOffset(double offset);

    void sendToUIGetPrintOption(QString option);
    void sendToUIGetInfoSetting(QString path,QString option);

    void sendToUIProductInfo(QString json);

    void sendToUIAutoReboot(bool value);

public slots:
    void receiveFromUIPrintUnlock();
    void receiveFromUIPrintStart(QVariantList args);

    void receiveFromUIPrintStateChange(QString CMD);

    void receiveFromUIGetMaterialList();

    void receiveFromUIGetPrintInfoToWeb();                    // when print time calc finish, send to web info

    int receiveFromUIGetHeightOffset();
    double receiveFromUIGetLedOffset();

    QString receiveFromUIGetPrintOption();
    QString receiveFromUIGetInfoSetting(QString path);

    void receiveFromUISetPrintTime(int time);       //for real time
    //use only qml or scheduler

    void receiveFromUIPrintFinishError();

    void receiveFromUISetHeightOffset(int value);
    void receiveFromUISetLedOffset(double value);

    void receiveFromUIBusySet(bool bs);
    void receiveFromUIShutdown();

    void receiveFromUIMoveMotor(QString cmd,int micro);

    void receiveFromUIGetProductInfo();

    void receiveFromUIGetUsbPortError();

    void receiveFromUpdaterFirmUpdate(QString path);

    void receiveFromUIAutoReboot();


public:
    BedSerialport* bedSerialPort = nullptr;

private:
    PrinterSetting _printerSetting;
    Version _version;

    BedControl* _bedControl;

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


    int _progress = 0;
    long long _lastStartTime = 0;
    long long _elapsedTime = 0;
    double _layerHeight = 0.0;
    long long _totalPrintTime = 0;
    QString _printState = "ready"; //ready, error, print, lock

    int _bedCuringLayer = 5;
    int _bedCuringTime = 0;
    int _curingTime = 0;
    int _printDelay = 0;

    bool _totalTimeCalc = true;


    int _printTime = 0;

    bool _enableTimer = false;

    bool _bedError = false;

    bool _isBusy;

    bool _LCDState = true;
    bool _USBPortConnection = true;
};

#endif // PRINTSCHEDULER_H
