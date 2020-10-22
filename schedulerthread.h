#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H

#include <QObject>
#include <QThread>
#include "qmlconnecter.h"
#include "updateconnector.h"

class PrintScheduler;
class QQmlApplicationEngine;
class SchedulerThread : public QThread
{
    Q_OBJECT
public:
    SchedulerThread();
    SchedulerThread(QQmlApplicationEngine& engine, QmlConnecter& conn,UpdateConnector& update);

    PrintScheduler *sched() const;

private:
    virtual void run() override;
    QQmlApplicationEngine& _engine;

    PrintScheduler* _sched;
    QmlConnecter& _conn;
    UpdateConnector& _updater;
};

#endif // SCHEDULERTHREAD_H
