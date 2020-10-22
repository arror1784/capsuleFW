#include "schedulerthread.h"

#include <QQmlContext>

#include "printscheduler.h"
#include "networkcontrol.h"
#include "resinupdater.h"
#include "updater.h"
#include "wpa.h"
#include "websocketclient.h"

SchedulerThread::SchedulerThread(QQmlApplicationEngine &engine, QmlConnecter &conn) : _engine(engine), _conn(conn)
{

}

void SchedulerThread::run()
{

    qDebug() << "sched" << QThread::currentThread();

    _sched = new PrintScheduler();

    _conn.schedConnect(_sched);

    NetworkControl nc;
    ResinUpdater ru(_sched);
    Updater up;
//    WPA wpa;

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

//    wsClient.open();

//    std::function<void()> func = [this,&nc,&ru,&up/*,&wpa*/]() {
//        qDebug() << "func" << QThread::currentThread();
//        QQmlContext* ctx = _engine.rootContext();

//        ctx->setContextProperty("nc",&nc);
//        ctx->setContextProperty("resinUpdater",&ru);
//        ctx->setContextProperty("SWUpdater",&up);
////        ctx->setContextProperty("wifi",&wpa);

//        _engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
////        _engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
//    };

//    QMetaObject::invokeMethod(this,func,Qt::QueuedConnection);

    QObject::connect(&up,&Updater::updateMCUFirmware,_sched,&PrintScheduler::receiveFromUpdaterFirmUpdate);
    QObject::connect(_sched,&PrintScheduler::MCUFirmwareUpdateFinished,&up,&Updater::MCUFirmwareUpdateFinished);

    QThread::exec();
}

PrintScheduler *SchedulerThread::sched() const
{
    return _sched;
}
