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
    WPA wpa;

    WebSocketClient wsClient(QUrl(QStringLiteral("ws://localhost:8000/ws/printer")));
    QObject::connect(&wsClient,&WebSocketClient::startByWeb,_sched,&PrintScheduler::receiveFromUIPrintStart);
    QObject::connect(&wsClient,&WebSocketClient::pauseByWeb,_sched,&PrintScheduler::receiveFromUIPrintPause);
    QObject::connect(&wsClient,&WebSocketClient::resumeByWeb,_sched,&PrintScheduler::receiveFromUIPrintResume);
    QObject::connect(&wsClient,&WebSocketClient::finishByWeb,_sched,&PrintScheduler::receiveFromUIPrintFinish);
    QObject::connect(&wsClient,&WebSocketClient::getMaterialListbyWeb,_sched,&PrintScheduler::receiveFromUIGetMaterialList);
    QObject::connect(&wsClient,&WebSocketClient::getPrintInfoByWeb,_sched,&PrintScheduler::receiveFromUIGetPrintInfoToWeb);


    QObject::connect(_sched,&PrintScheduler::sendToUIUpdateProgress,&wsClient,&WebSocketClient::updateProgressToWeb);

    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrint,&wsClient,&WebSocketClient::changeToPrintToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPauseStart,&wsClient,&WebSocketClient::changeToPauseStartToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPauseFinish,&wsClient,&WebSocketClient::changeToPauseFinishToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToResume,&wsClient,&WebSocketClient::changeToResumeToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToQuit,&wsClient,&WebSocketClient::changeToQuitToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrintFinish,&wsClient,&WebSocketClient::changeToPrintFinishToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrintWorkError,&wsClient,&WebSocketClient::changeToPrintWorkErrorToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIChangeToPrintWorkErrorFinish,&wsClient,&WebSocketClient::changeToPrintWorkErrorFinishToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUIPrintSettingError,&wsClient,&WebSocketClient::changeToPrintSettingErrorToWeb);

    QObject::connect(_sched,&PrintScheduler::sendToUIMaterialList,&wsClient,&WebSocketClient::materialListToWeb);

    QObject::connect(_sched,&PrintScheduler::sendToUIEnableTimer,&wsClient,&WebSocketClient::enableTimer);

    QObject::connect(_sched,&PrintScheduler::sendToUIPrintInfo,&wsClient,&WebSocketClient::getPrintInfoToWeb);
    QObject::connect(_sched,&PrintScheduler::sendToUISetTotalTime,&wsClient,&WebSocketClient::setTotalTime);

    wsClient.open();

//    std::function<void()> func = [this,&nc,&ru,&up,&wpa]() {
//        qDebug() << "func" << QThread::currentThread();
//        QQmlContext* ctx = _engine.rootContext();

//        ctx->setContextProperty("scheduler",_sched);
//        ctx->setContextProperty("nc",&nc);
//        ctx->setContextProperty("resinUpdater",&ru);
//        ctx->setContextProperty("SWUpdater",&up);
//        ctx->setContextProperty("wifi",&wpa);

//        _engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
////        _engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));

//        auto object = _engine.rootObjects().first();

//        QObject::connect(_sched,SIGNAL(sendToUITESTSIG()),object,SLOT(receiveCPPslot()));
//        QObject::connect(object,SIGNAL(testQMLSIG2()),_sched,SLOT(receiveFromQMLTEST2()));
//        QObject::connect(object,SIGNAL(testQMLSIG()),_sched,SLOT(receiveFromQMLTEST()));

//    };

//    QMetaObject::invokeMethod(this,func,Qt::QueuedConnection);

//    _sched->sendToUITESTSIG();

    QObject::connect(&up,&Updater::updateMCUFirmware,_sched,&PrintScheduler::receiveFromUpdaterFirmUpdate);
    QObject::connect(_sched,&PrintScheduler::MCUFirmwareUpdateFinished,&up,&Updater::MCUFirmwareUpdateFinished);

    QThread::exec();
}

PrintScheduler *SchedulerThread::sched() const
{
    return _sched;
}
