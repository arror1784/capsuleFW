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
    void sendToSchedPrintStart(QVariantList args);
    void sendToSchedPrintStateChange(QString CMD);
    void sendToSchedGetMaterialList();
    void sendToSchedGetPrintInfoToWeb();                    // when print time calc finish, send to web info
    int sendToSchedGetHeightOffset();
    double sendToSchedGetLedOffset();
    QString sendToSchedGetPrintOption();
    QString sendToSchedGetInfoSetting(QString path);
    void sendToSchedSetPrintTime(int time);
    void sendToSchedSetHeightOffset(int value);
    void sendToSchedSetLedOffset(double value);
    void sendToSchedBusySet(bool bs);
    void sendToSchedShutdown();
    void sendToSchedMoveMotor(QString cmd,int micro);
    void sendToSchedGetProductInfo();
    void sendToSchedGetUsbPortError();

    void sendToSchedAutoReboot();


    void sendToQmlChangeImage(QString imagePath);
    void sendToQmlSetImageScale(double value);
    void sendToQmlUpdateProgress(int progress);
    void sendToQmlChangeToPrint();
    void sendToQmlChangeState(QString state);
    void sendToQmlPrintSettingError(int code);
    void sendToQmlEnableTimer(bool enable);
    void sendToQmlMaterialList(QVariantList name);
    void sendToQmlPrintInfo(QString printerState,QString material, QString fileName,double layerHeight,int elapsedTime,int totalTime,int progress,bool enableTimer);
    void sendToQmlSetTotalTime(int time);
    void sendToQmlPortOpenError(bool value);
    void sendToQmlLCDState(bool state);
    void sendToQmlExit(bool error);
    void sendToQmlMoveOk();
    void sendToQmlHeightOffset(int offset);
    void sendToQmlLEDOffset(double offset);
    void sendToQmlGetPrintOption(QString option);
    void sendToQmlGetInfoSetting(QString path,QString option);
    void sendToQmlProductInfo(QString json);

    void sendToQmlAutoReboot(bool value);


public slots:
    void receiveFromQmlPrintStart(QVariantList args){emit sendToSchedPrintStart(args);}
    void receiveFromQmlPrintStateChange(QString CMD){emit sendToSchedPrintStateChange(CMD);}
    void receiveFromQmlGetMaterialList(){emit sendToSchedGetMaterialList();}
    void receiveFromQmlGetPrintInfoToWeb(){emit sendToSchedGetPrintInfoToWeb();}                    // when print time calc finish, send to web info
    void receiveFromQmlGetHeightOffset(){emit sendToSchedGetHeightOffset();}
    void receiveFromQmlGetLedOffset(){emit sendToSchedGetLedOffset();}
    void receiveFromQmlGetPrintOption(){emit sendToSchedGetPrintOption();}
    void receiveFromQmlGetInfoSetting(QString path){emit sendToSchedGetInfoSetting(path);}
    void receiveFromQmlSetPrintTime(int time){emit sendToSchedSetPrintTime(time);}
    void receiveFromQmlSetHeightOffset(int value){emit sendToSchedSetHeightOffset(value);}
    void receiveFromQmlSetLedOffset(double value){emit sendToSchedSetLedOffset(value);}
    void receiveFromQmlBusySet(bool bs){emit sendToSchedBusySet(bs);}
    void receiveFromQmlShutdown(){emit sendToSchedShutdown();}
    void receiveFromQmlMoveMotor(QString cmd,int micro){emit sendToSchedMoveMotor(cmd,micro);}
    void receiveFromQmlGetProductInfo(){emit sendToSchedGetProductInfo();}
    void receiveFromQmlGetUsbPortError(){emit sendToSchedGetUsbPortError();}

    void receiveFromQmlAutoReboot(){emit sendToSchedAutoReboot();}

    void receiveFromSchedChangeImage(QString imagePath){emit sendToQmlChangeImage(imagePath);}
    void receiveFromSchedSetImageScale(double value){emit sendToQmlSetImageScale(value);}
    void receiveFromSchedUpdateProgress(int progress){emit sendToQmlUpdateProgress(progress);}
    void receiveFromSchedChangeToPrint(){emit sendToQmlChangeToPrint();}
    void receiveFromSchedChangeState(QString state){emit sendToQmlChangeState(state);}
    void receiveFromSchedPrintSettingError(int code){emit sendToQmlPrintSettingError(code);}
    void receiveFromSchedEnableTimer(bool enable){emit sendToQmlEnableTimer(enable);}
    void receiveFromSchedMaterialList(QVariantList name){emit sendToQmlMaterialList(name);}
    void receiveFromSchedPrintInfo(QString printerState,QString material, QString fileName,double layerHeight,int elapsedTime,int totalTime,int progress,bool enableTimer)
    {emit sendToQmlPrintInfo(printerState,material,fileName,layerHeight,elapsedTime,totalTime,progress,enableTimer);}
    void receiveFromSchedSetTotalTime(int time){emit sendToQmlSetTotalTime(time);}
    void receiveFromSchedPortOpenError(bool value){emit sendToQmlPortOpenError(value);}
    void receiveFromSchedLCDState(bool state){emit sendToQmlLCDState(state);}
    void receiveFromSchedExit(bool error){emit sendToQmlExit(error);}
    void receiveFromSchedMoveOk(){emit sendToQmlMoveOk();}
    void receiveFromSchedHeightOffset(int offset){emit sendToQmlHeightOffset(offset);}
    void receiveFromSchedLEDOffset(double offset){emit sendToQmlLEDOffset(offset);}
    void receiveFromSchedGetPrintOption(QString option){emit sendToQmlGetPrintOption(option);}
    void receiveFromSchedGetInfoSetting(QString path,QString option){emit sendToQmlGetInfoSetting(path,option);}
    void receiveFromSchedProductInfo(QString json){emit sendToQmlProductInfo(json);}

    void receiveFromSchedAutoReboot(bool value){emit sendToQmlAutoReboot(value);}

private:
    PrintScheduler* _sched;

};

#endif // CONNECTERSINGLE_H
