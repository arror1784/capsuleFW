#include "qmlconnecter.h"

#include <QString>

QmlConnecter::QmlConnecter()
{

}

void QmlConnecter::schedConnect(PrintScheduler *sched)
{
    _sched = sched;
    {
        QObject::connect(this,&QmlConnecter::sendToSchedPrintStart,_sched,&PrintScheduler::receiveFromUIPrintStart);
        QObject::connect(this,&QmlConnecter::sendToSchedPrintStateChange,_sched,&PrintScheduler::receiveFromUIPrintStateChange);
        QObject::connect(this,&QmlConnecter::sendToSchedGetMaterialList,_sched,&PrintScheduler::receiveFromUIGetMaterialList);
        QObject::connect(this,&QmlConnecter::sendToSchedGetPrintInfoToWeb,_sched,&PrintScheduler::receiveFromUIGetPrintInfoToWeb);
        QObject::connect(this,&QmlConnecter::sendToSchedGetHeightOffset,_sched,&PrintScheduler::receiveFromUIGetHeightOffset);
        QObject::connect(this,&QmlConnecter::sendToSchedGetLedOffset,_sched,&PrintScheduler::receiveFromUIGetLedOffset);
        QObject::connect(this,&QmlConnecter::sendToSchedGetPrintOption,_sched,&PrintScheduler::receiveFromUIGetPrintOption);
        QObject::connect(this,&QmlConnecter::sendToSchedGetInfoSetting,_sched,&PrintScheduler::receiveFromUIGetInfoSetting);
        QObject::connect(this,&QmlConnecter::sendToSchedSetPrintTime,_sched,&PrintScheduler::receiveFromUISetPrintTime);
        QObject::connect(this,&QmlConnecter::sendToSchedSetHeightOffset,_sched,&PrintScheduler::receiveFromUISetHeightOffset);
        QObject::connect(this,&QmlConnecter::sendToSchedSetLedOffset,_sched,&PrintScheduler::receiveFromUISetLedOffset);
        QObject::connect(this,&QmlConnecter::sendToSchedBusySet,_sched,&PrintScheduler::receiveFromUIBusySet);
        QObject::connect(this,&QmlConnecter::sendToSchedShutdown,_sched,&PrintScheduler::receiveFromUIShutdown);
        QObject::connect(this,&QmlConnecter::sendToSchedMoveMotor,_sched,&PrintScheduler::receiveFromUIMoveMotor);
        QObject::connect(this,&QmlConnecter::sendToSchedGetProductInfo,_sched,&PrintScheduler::receiveFromUIGetProductInfo);
        QObject::connect(this,&QmlConnecter::sendToSchedGetUsbPortError,_sched,&PrintScheduler::receiveFromUIGetUsbPortError);
        QObject::connect(this,&QmlConnecter::sendToSchedAutoReboot,_sched,&PrintScheduler::receiveFromUIAutoReboot);

        QObject::connect(_sched,&PrintScheduler::sendToLCDChangeImage,this,&QmlConnecter::receiveFromSchedChangeImage);
        QObject::connect(_sched,&PrintScheduler::sendToLCDSetImageScale,this,&QmlConnecter::receiveFromSchedSetImageScale);
        QObject::connect(_sched,&PrintScheduler::sendToUIUpdateProgress,this,&QmlConnecter::receiveFromSchedUpdateProgress);
        QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrint,this,&QmlConnecter::receiveFromSchedChangeToPrint) ;
        QObject::connect(_sched,&PrintScheduler::sendToUIChangeState,this,&QmlConnecter::receiveFromSchedChangeState);
        QObject::connect(_sched,&PrintScheduler::sendToUIPrintSettingError,this,&QmlConnecter::receiveFromSchedPrintSettingError);
        QObject::connect(_sched,&PrintScheduler::sendToUIEnableTimer,this,&QmlConnecter::receiveFromSchedEnableTimer);
        QObject::connect(_sched,&PrintScheduler::sendToUIMaterialList,this,&QmlConnecter::receiveFromSchedMaterialList);
        QObject::connect(_sched,&PrintScheduler::sendToUIPrintInfo,this,&QmlConnecter::receiveFromSchedPrintInfo);
        QObject::connect(_sched,&PrintScheduler::sendToUISetTotalTime,this,&QmlConnecter::receiveFromSchedSetTotalTime);
        QObject::connect(_sched,&PrintScheduler::sendToUIPortOpenError,this,&QmlConnecter::receiveFromSchedPortOpenError);
        QObject::connect(_sched,&PrintScheduler::sendToUILCDState,this,&QmlConnecter::receiveFromSchedLCDState);
        QObject::connect(_sched,&PrintScheduler::sendToUIExit,this,&QmlConnecter::receiveFromSchedExit);
        QObject::connect(_sched,&PrintScheduler::sendToUIMoveOk,this,&QmlConnecter::receiveFromSchedMoveOk);
        QObject::connect(_sched,&PrintScheduler::sendToUIHeightOffset,this,&QmlConnecter::receiveFromSchedHeightOffset);
        QObject::connect(_sched,&PrintScheduler::sendToUILEDOffset,this,&QmlConnecter::receiveFromSchedLEDOffset);
        QObject::connect(_sched,&PrintScheduler::sendToUIGetPrintOption,this,&QmlConnecter::receiveFromSchedGetPrintOption);
        QObject::connect(_sched,&PrintScheduler::sendToUIGetInfoSetting,this,&QmlConnecter::receiveFromSchedGetInfoSetting);
        QObject::connect(_sched,&PrintScheduler::sendToUIProductInfo,this,&QmlConnecter::receiveFromSchedProductInfo);
        QObject::connect(_sched,&PrintScheduler::sendToUIAutoReboot,this,&QmlConnecter::receiveFromSchedAutoReboot);

    }
}
