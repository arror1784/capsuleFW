﻿#include "schedulerthread.h"

#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "printscheduler.h"
#include "networkcontrol.h"
#include "resinupdater.h"
#include "updater.h"
#include "wpa.h"
#include "websocketclient.h"

#include "l10imageprovider.h"
#include "printimage.h"

SchedulerThread::SchedulerThread(QQmlApplicationEngine &engine, QmlConnecter &conn,UpdateConnector& update,PrintImage* printImage)
    : _engine(engine), _conn(conn), _updater(update), _printImage(printImage)
{

}

void SchedulerThread::run()
{
    L10ImageProvider l10ImageProvider;
    _sched = new PrintScheduler(&l10ImageProvider,_printImage);
    ResinUpdater ru(_sched);
    Updater up;

    QObject::connect(&up,&Updater::updateMCUFirmware,_sched,&PrintScheduler::receiveFromUpdaterFirmUpdate);
    QObject::connect(_sched,&PrintScheduler::MCUFirmwareUpdateFinished,&up,&Updater::MCUFirmwareUpdateFinished);

    _conn.schedConnect(_sched);
    _updater.swUpdaterConnect(&up);
    _updater.resinUpdaterConnect(&ru);

    WebSocketClient wsClient(QUrl(QStringLiteral("ws://localhost:8000/ws/printer")));

    QObject::connect(&wsClient,&WebSocketClient::startByWeb,_sched,&PrintScheduler::receiveFromUIPrintStart);
    QObject::connect(&wsClient,&WebSocketClient::changeStateByWeb,_sched,&PrintScheduler::receiveFromUIPrintStateChange);
    QObject::connect(&wsClient,&WebSocketClient::getMaterialListbyWeb,_sched,&PrintScheduler::receiveFromUIGetMaterialList);
    QObject::connect(&wsClient,&WebSocketClient::getPrintInfoByWeb,_sched,&PrintScheduler::receiveFromUIGetPrintInfoToWeb);


    QObject::connect(_sched,&PrintScheduler::sendToUIUpdateProgress,&wsClient,&WebSocketClient::updateProgressToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrint,&wsClient,&WebSocketClient::changeToPrintToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeState,&wsClient,&WebSocketClient::changeToStateToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIPrintSettingError,&wsClient,&WebSocketClient::changeToPrintSettingErrorToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIMaterialList,&wsClient,&WebSocketClient::materialListToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIEnableTimer,&wsClient,&WebSocketClient::enableTimer);
    QObject::connect(_sched,&PrintScheduler::sendToUIPrintInfo,&wsClient,&WebSocketClient::getPrintInfoToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUISetTotalTime,&wsClient,&WebSocketClient::setTotalTime);
#ifdef __arm__
    wsClient.open();
#endif
//    wsClient.open();

    std::function<void()> func = [this,&l10ImageProvider]() {

        _engine.addImageProvider(QLatin1String("L10"), &l10ImageProvider);


#ifdef __arm__
        _engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
        _engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
#else
        _engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
        _engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));

#ifdef MCU_UPDATE_TEST
        _updater.sendToSWMCUUpdate("/home/jsh/KinematicFW_F446.binary");
#endif

#endif
    };

    QMetaObject::invokeMethod(&_engine,func,Qt::QueuedConnection);

    QThread::exec();
}

PrintScheduler *SchedulerThread::sched() const
{
    return _sched;
}
