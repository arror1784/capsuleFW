#ifndef CONNECTERSINGLE_H
#define CONNECTERSINGLE_H

#include <QObject>
#include "printscheduler.h"

class QmlConnecter : public QObject
{
    Q_OBJECT
public:
    QmlConnecter();

    void schedConnect(PrintScheduler* sched);



signals:

    void sendTOQMLPrintStart(QString path,QString materialName);
    void sendToSchedPrintStart(QString fileName,QString materialName,QJsonObject byte);
    void sendToSchedPrintAgain();
    void sendToSchedPrintResume();
    void sendToSchedPrintPause();
    void sendToSchedPrintFinish();
    void sendToSchedGetMaterialList();
    void sendToSchedGetPrintInfoToWeb();
    int sendToSchedGetHeightOffset();
    double sendToSchedGetLedOffset();
    QString sendToSchedGetMaterialOption(QString material);
    QString sendToSchedGetPrintOption();
    QString sendToSchedGetInfoSetting(QString path);
    void sendToSchedSetTotalPrintTime(int time);
    void sendToSchedPrintFinishError();
    void sendToSchedSetHeightOffset(int value);
    void sendToSchedSetLedOffset(double value);
    bool isCustom(QString path);
    void sendToSchedBusySet(bool bs);
    void sendToSchedShutdown();
    void sendToSchedGoHome();
    void sendToSchedAutoHome();
    void sendToSchedMoveMicro(int micro);
    void sendToSchedMoveMaxHeight();
    void sendToSchedGetVersion();
    void sendToSchedGetModelNo();
    void sendToSchedSetPrintTime(int time);
    void receiveFromUpdaterFirmUpdate(QString path);

public slots:

    void receiveChangeImage(QString imagePath){}
    void receiveSetImageScale(double value){}
    void receiveUpdateProgress(int progress){}
    void receiveFirstlayerStart(){}
    void receiveFirstlayerFinish(){}
    void receiveChangeToPrint(){}
    void receiveChangeToPauseStart(){}
    void receiveChangeToPauseFinish(){}
    void receiveChangeToResume(){}
    void receiveChangeToQuit(){}
    void receiveChangeToPrintFinish(){}
    void receiveChangeToPrintWorkError(){}
    void receiveChangeToPrintWorkErrorFinish(){}
    void receivePrintSettingError(int code){}
    void receiveEnableTimer(bool enable){}
    void receiveMaterialList(QVariantList name){}
    void receivePrintInfo(QString printerState,QString material, QString fileName,double layerHeight,int elapsedTime,int totalTime,int progress,bool enableTimer){}
    void receiveSetTotalTime(int time){}
    void receivePortOpenError(){}
    void receiveLCDState(bool state){}
    void receiveExitError(){}
    void receiveExit(){}
    void receiveMoveOk(){}
    void MCUFirmwareUpdateFinished(){}
    void receiveSWUpdateAvailable(){}
    void receiveSWUpdateNotAvailable(){}
    void receiveSWUpdateFinished(){}
    void receiveSWUpdateError(){}
    void receiveHeightOffset(int offset){}
    void receiveLEDOffset(double offset){}
    void receiveMaterialOption(QString material,QString option){}
    void receiveGetPrintOption(QString option){}
    void receiveGetInfoSetting(QString path,QString option){}
    void receiveIsCustom(bool value){}
    void receiveVersion(QString version){}
    void receiveModelNo(QString modelNo){}

private:
    PrintScheduler* _sched;

};

#endif // CONNECTERSINGLE_H
