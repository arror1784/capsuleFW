#include "qmlconnecter.h"

#include <QString>

QmlConnecter::QmlConnecter()
{

}

void QmlConnecter::schedConnect(PrintScheduler *sched)
{
    _sched = sched;
    {
    QObject::connect(this,&QmlConnecter::sendTOQMLPrintStart,_sched,&PrintScheduler::receiveFromQMLPrintStart);
    QObject::connect(this,&QmlConnecter::sendToSchedPrintStart,_sched,&PrintScheduler::receiveFromUIPrintStart);
    QObject::connect(this,&QmlConnecter::sendToSchedPrintAgain,_sched,&PrintScheduler::receiveFromUIPrintAgain);
    QObject::connect(this,&QmlConnecter::sendToSchedPrintResume,_sched,&PrintScheduler::receiveFromUIPrintResume);
    QObject::connect(this,&QmlConnecter::sendToSchedPrintPause,_sched,&PrintScheduler::receiveFromUIPrintPause);
    QObject::connect(this,&QmlConnecter::sendToSchedPrintFinish,_sched,&PrintScheduler::receiveFromUIPrintFinish);
    QObject::connect(this,&QmlConnecter::sendToSchedGetMaterialList,_sched,&PrintScheduler::receiveFromUIGetMaterialList);
    QObject::connect(this,&QmlConnecter::sendToSchedGetPrintInfoToWeb,_sched,&PrintScheduler::receiveFromUIGetPrintInfoToWeb);
    QObject::connect(this,&QmlConnecter::sendToSchedGetHeightOffset,_sched,&PrintScheduler::receiveFromUIGetHeightOffset);
    QObject::connect(this,&QmlConnecter::sendToSchedGetLedOffset,_sched,&PrintScheduler::receiveFromUIGetLedOffset);
    QObject::connect(this,&QmlConnecter::sendToSchedGetMaterialOption,_sched,&PrintScheduler::receiveFromUIGetMaterialOption);
    QObject::connect(this,&QmlConnecter::sendToSchedGetPrintOption,_sched,&PrintScheduler::receiveFromUIGetPrintOption);
    QObject::connect(this,&QmlConnecter::sendToSchedGetInfoSetting,_sched,&PrintScheduler::receiveFromUIGetInfoSetting);
    QObject::connect(this,&QmlConnecter::sendToSchedSetTotalPrintTime,_sched,&PrintScheduler::receiveFromUISetTotalPrintTime);
    QObject::connect(this,&QmlConnecter::sendToSchedPrintFinishError,_sched,&PrintScheduler::receiveFromUIPrintFinishError);
    QObject::connect(this,&QmlConnecter::sendToSchedSetHeightOffset,_sched,&PrintScheduler::receiveFromUISetHeightOffset);
    QObject::connect(this,&QmlConnecter::sendToSchedSetLedOffset,_sched,&PrintScheduler::receiveFromUISetLedOffset);
    QObject::connect(this,&QmlConnecter::isCustom,_sched,&PrintScheduler::isCustom);
    QObject::connect(this,&QmlConnecter::sendToSchedBusySet,_sched,&PrintScheduler::receiveFromUIBusySet);
    QObject::connect(this,&QmlConnecter::sendToSchedShutdown,_sched,&PrintScheduler::receiveFromUIShutdown);
    QObject::connect(this,&QmlConnecter::sendToSchedGoHome,_sched,&PrintScheduler::receiveFromUIGoHome);
    QObject::connect(this,&QmlConnecter::sendToSchedAutoHome,_sched,&PrintScheduler::receiveFromUIAutoHome);
    QObject::connect(this,&QmlConnecter::sendToSchedMoveMicro,_sched,&PrintScheduler::receiveFromUIMoveMicro);
    QObject::connect(this,&QmlConnecter::sendToSchedMoveMaxHeight,_sched,&PrintScheduler::receiveFromUIMoveMaxHeight);
    QObject::connect(this,&QmlConnecter::sendToSchedGetVersion,_sched,&PrintScheduler::receiveFromUIGetVersion);
    QObject::connect(this,&QmlConnecter::sendToSchedGetModelNo,_sched,&PrintScheduler::receiveFromUIGetModelNo);
    QObject::connect(this,&QmlConnecter::sendToSchedSetPrintTime,_sched,&PrintScheduler::receiveFromUISetPrintTime);
    QObject::connect(this,&QmlConnecter::receiveFromUpdaterFirmUpdate,_sched,&PrintScheduler::receiveFromUpdaterFirmUpdate);

    QObject::connect(_sched,&PrintScheduler::sendToLCDChangeImage,this,&QmlConnecter::receiveChangeImage);
    QObject::connect(_sched,&PrintScheduler::sendToLCDSetImageScale,this,&QmlConnecter::receiveSetImageScale);
    QObject::connect(_sched,&PrintScheduler::sendToUIUpdateProgress,this,&QmlConnecter::receiveUpdateProgress);
    QObject::connect(_sched,&PrintScheduler::sendToUIFirstlayerStart,this,&QmlConnecter::receiveFirstlayerStart);
    QObject::connect(_sched,&PrintScheduler::sendToUIFirstlayerFinish,this,&QmlConnecter::receiveFirstlayerFinish);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrint,this,&QmlConnecter::receiveChangeToPrint);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPauseStart,this,&QmlConnecter::receiveChangeToPauseStart);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPauseFinish,this,&QmlConnecter::receiveChangeToPauseFinish);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToResume,this,&QmlConnecter::receiveChangeToResume);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToQuit,this,&QmlConnecter::receiveChangeToQuit);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrintFinish,this,&QmlConnecter::receiveChangeToPrintFinish);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrintWorkError,this,&QmlConnecter::receiveChangeToPrintWorkError);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrintWorkErrorFinish,this,&QmlConnecter::receiveChangeToPrintWorkErrorFinish);
    QObject::connect(_sched,&PrintScheduler::sendToUIPrintSettingError,this,&QmlConnecter::receivePrintSettingError);
    QObject::connect(_sched,&PrintScheduler::sendToUIEnableTimer,this,&QmlConnecter::receiveEnableTimer);
    QObject::connect(_sched,&PrintScheduler::sendToUIMaterialList,this,&QmlConnecter::receiveMaterialList);
    QObject::connect(_sched,&PrintScheduler::sendToUIPrintInfo,this,&QmlConnecter::receivePrintInfo);
    QObject::connect(_sched,&PrintScheduler::sendToUISetTotalTime,this,&QmlConnecter::receiveSetTotalTime);
    QObject::connect(_sched,&PrintScheduler::sendToUIPortOpenError,this,&QmlConnecter::receivePortOpenError);
    QObject::connect(_sched,&PrintScheduler::sendToUILCDState,this,&QmlConnecter::receiveLCDState);
    QObject::connect(_sched,&PrintScheduler::sendToUIExitError,this,&QmlConnecter::receiveExitError);
    QObject::connect(_sched,&PrintScheduler::sendToUIExit,this,&QmlConnecter::receiveExit);
    QObject::connect(_sched,&PrintScheduler::sendToUIMoveOk,this,&QmlConnecter::receiveMoveOk);
    QObject::connect(_sched,&PrintScheduler::MCUFirmwareUpdateFinished,this,&QmlConnecter::MCUFirmwareUpdateFinished);
    QObject::connect(_sched,&PrintScheduler::sendToUISWUpdateAvailable,this,&QmlConnecter::receiveSWUpdateAvailable);
    QObject::connect(_sched,&PrintScheduler::sendToUISWUpdateNotAvailable,this,&QmlConnecter::receiveSWUpdateNotAvailable);
    QObject::connect(_sched,&PrintScheduler::sendToUISWUpdateFinished,this,&QmlConnecter::receiveSWUpdateFinished);
    QObject::connect(_sched,&PrintScheduler::sendToUISWUpdateError,this,&QmlConnecter::receiveSWUpdateError);
    QObject::connect(_sched,&PrintScheduler::sendToUIHeightOffset,this,&QmlConnecter::receiveHeightOffset);
    QObject::connect(_sched,&PrintScheduler::sendToUILEDOffset,this,&QmlConnecter::receiveLEDOffset);
    QObject::connect(_sched,&PrintScheduler::sendToUIMaterialOption,this,&QmlConnecter::receiveMaterialOption);
    QObject::connect(_sched,&PrintScheduler::sendToUIGetPrintOption,this,&QmlConnecter::receiveGetPrintOption);
    QObject::connect(_sched,&PrintScheduler::sendToUIGetInfoSetting,this,&QmlConnecter::receiveGetInfoSetting);
    QObject::connect(_sched,&PrintScheduler::sendToUIIsCustom,this,&QmlConnecter::receiveIsCustom);
    QObject::connect(_sched,&PrintScheduler::sendToUIVersion,this,&QmlConnecter::receiveVersion);
    QObject::connect(_sched,&PrintScheduler::sendToUIModelNo,this,&QmlConnecter::receiveModelNo);
    }
}
