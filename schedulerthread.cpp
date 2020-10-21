#include "schedulerthread.h"

#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "printscheduler.h"
#include "networkcontrol.h"
#include "resinupdater.h"
#include "updater.h"
#include "wpa.h"

SchedulerThread::SchedulerThread(QQmlApplicationEngine &engine) : _engine(engine)
{

}

void SchedulerThread::run()
{

    qDebug() << "sched" << QThread::currentThread();

    _sched = new PrintScheduler();

    NetworkControl nc;
    ResinUpdater ru(_sched);
    Updater up;
    WPA wpa;

    std::function<void()> func = [this,&nc,&ru,&up,&wpa]() {
        qDebug() << "func" << QThread::currentThread();
        QQmlContext* ctx = _engine.rootContext();

        ctx->setContextProperty("scheduler",_sched);
        ctx->setContextProperty("nc",&nc);
        ctx->setContextProperty("resinUpdater",&ru);
        ctx->setContextProperty("SWUpdater",&up);
        ctx->setContextProperty("wifi",&wpa);

        _engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
        _engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);


    QObject::connect(&up,&Updater::updateMCUFirmware,_sched,&PrintScheduler::receiveFromUpdaterFirmUpdate);
    QObject::connect(_sched,&PrintScheduler::MCUFirmwareUpdateFinished,&up,&Updater::MCUFirmwareUpdateFinished);

    QThread::exec();
}

PrintScheduler *SchedulerThread::sched() const
{
    return _sched;
}
