#include "schedulerthread.h"

#include <QQmlContext>

#include "printscheduler.h"
#include "networkcontrol.h"
#include "resinupdater.h"
#include "updater.h"
#include "wpa.h"

SchedulerThread::SchedulerThread(QQmlApplicationEngine &engine) : _engine(engine)
{
    QThread::start();
}

void SchedulerThread::run()
{
    QQmlContext* ctx = _engine.rootContext();

    _sched = new PrintScheduler();

    NetworkControl nc;
    ResinUpdater ru(_sched);
    Updater up;
    WPA wpa;

    ctx->setContextProperty("scheduler",_sched);
    ctx->setContextProperty("nc",&nc);
    ctx->setContextProperty("resinUpdater",&ru);
    ctx->setContextProperty("SWUpdater",&up);
    ctx->setContextProperty("wifi",&wpa);

    QObject::connect(&up,&Updater::updateMCUFirmware,_sched,&PrintScheduler::receiveFromUpdaterFirmUpdate);
    QObject::connect(_sched,&PrintScheduler::MCUFirmwareUpdateFinished,&up,&Updater::MCUFirmwareUpdateFinished);

    QThread::exec();
}

PrintScheduler *SchedulerThread::sched() const
{
    return _sched;
}
