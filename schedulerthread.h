#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H

#include <QObject>
#include <QThread>

class PrintScheduler;
class QQmlApplicationEngine;
class SchedulerThread : public QThread
{
    Q_OBJECT
public:
    SchedulerThread(QQmlApplicationEngine& engine);

    PrintScheduler *sched() const;

private:
    virtual void run() override;
    QQmlApplicationEngine& _engine;

    PrintScheduler* _sched;
};

#endif // SCHEDULERTHREAD_H
