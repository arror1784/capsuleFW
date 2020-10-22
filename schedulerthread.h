#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H

#include <QObject>
#include <QThread>
#include "qmlconnecter.h"

class PrintScheduler;
class QQmlApplicationEngine;
class SchedulerThread : public QThread
{
    Q_OBJECT
public:
    SchedulerThread();
    SchedulerThread(QQmlApplicationEngine& engine, QmlConnecter& conn);

    PrintScheduler *sched() const;

private:
    virtual void run() override;
    QQmlApplicationEngine& _engine;

    PrintScheduler* _sched;
    QmlConnecter& _conn;
};

#endif // SCHEDULERTHREAD_H
