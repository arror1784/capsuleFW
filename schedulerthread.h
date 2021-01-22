#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H

#include <QObject>
#include <QThread>
#include "qmlconnecter.h"
#include "updateconnector.h"
#include "printimage.h"

class PrintScheduler;
class QQmlApplicationEngine;
class SchedulerThread : public QThread
{
    Q_OBJECT
public:
    SchedulerThread();
    SchedulerThread(QQmlApplicationEngine& engine, QmlConnecter& conn,UpdateConnector& update,PrintImage* printImage);

    PrintScheduler *sched() const;

private:
    void run() override;

    QQmlApplicationEngine& _engine;

    PrintScheduler* _sched;
    PrintImage* _printImage;
    QmlConnecter& _conn;
    UpdateConnector& _updater;
};

#endif // SCHEDULERTHREAD_H
