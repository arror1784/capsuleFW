
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

#include "iostream"
#include "logger.h"

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

    int copyProject(QString path);
    int copyFilesPath(QString src, QString dst);
    int setupForPrint(QString materialName);

//    int readyForPrintStart(QString materialName,QString path); // info.json

    void receiveFromBedControl(int state);
    void receiveFromSerialPort(int state);

    void setVersion(const QString &version);

signals:
    void sendToQmlChangeImage(QString imagePath);
//    void sendToQmlChangeDefault();
    void sendToQmlSetImageScale(double value);

    void sendToQmlPauseFinish();
    void sendToQmlPrintFinish();
    void sendToQmlUpdateProgress(int currentIndex,int maxIndex);

    void sendToQmlInit();
    void sendToQmlFinish();

    void sendToQmlInsertMaterialList(QString name);
    void sendToQmlMoveOk();
//    void sendToSerialPortCommand(QString);
    void sendToQmlPrintSettingError();
    void sendToQmlPrintWorkError();
    void sendToqmlPrintWorkErrorFinish();

    void sendToQmlWaitForMovement();

    void sendToQmlExitError();
    void sendToQmlExit();

    void sendToLCDState(int state);

    void sendToFirmwareUpdateFinish();
    void sendToFirmwareUpdateError();
    void sendToFirmwareUpdateProgrese(int progress);

    void sendToQmlFirstlayerStart();
    void sendToQmlFirstlayerFinish();

public slots:

    void receiveFromQmlBusySet(bool bs);

    void receiveFromQmlFirmUpdate(QString path);
    void receiveFromQmlShutdown();

    void receiveFromQmlBedPrint(QString path,QString materialName);
    void receiveFromQmlBedPrintAgain();

    void receiveFromQmlBedPrintStart();
    void receiveFromQmlBedPrintFinish();
    void receiveFromQmlBedPrintFinishError();
    void receiveFromQmlBedPrintPause();

    void receiveFromQmlUpdateMaterial();

    QVariant receiveFromQmlGetPrinterOption(QString key);
    void receiveFromQmlSetPrinterOption(QString key,double value);
    void receiveFromQmlSetPrinterOption(QString key,int value);
    void receiveFromQmlSetPrinterOption(QString key,QString value);
    QVariant receiveFromQmlGetMaterialOption(QString material,QString key);
    QVariant receiveFromQmlGetMaterialOptionFromPath(QString path,QString key);

    void receiveFromQmlGoHome();
    void receiveFromQmlAutoHome();
    void receiveFromQmlMoveMicro(int micro);
    void receiveFromQmlMoveMaxHeight();

    QString receiveFromQmlGetVersion();

    void receiveFromQmlSetPrintTime(int time);

public:
    BedSerialport* bedSerialPort = nullptr;
    QString printFilePath;

    QQmlApplicationEngine *engine;

    QString materialName() const;

    void setMotorSpendtime();
protected:
    void run()override;

private:
    BedControl* _bedControl;
    WebSocketClient *_wsClient;

    QString _version;

    int bedCuringLayer = 5;

    QString _fileExtension = ".png";

    QString printUSBFileName = "capsulePrintFolderTest";

    QString _bedPath;

    QString _printName;
    QString _materialName;

    QString _portPath;

    int _bedPrintImageNum;
    int _bedWork;
    int _bedMoveFinished;
    int _bedMaxPrintNum;

    int _printTime = 0;

    bool _bedError = false;

    bool _isBusy;

};

//extern PrintScheduler* printScheduler;

#endif // PRINTSCHEDULER_H
