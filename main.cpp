﻿#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSerialPort/QSerialPort>

#include <QThread>
#include <QQmlContext>

#include "bedserialport.h"
#include "bedcontrol.h"
#include "printscheduler.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    PrintScheduler* printScheduler = new PrintScheduler();

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();

    char buff[1024] = {0};
    ctx->setContextProperty("scheduler",printScheduler);

    engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
//    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    printScheduler->addSerialPort(QStringLiteral("/dev/ttyACM0"));
//    printScheduler->addSerialPort(QStringLiteral("ttyUSB0"));
//    printScheduler->addSerialPort(QStringLiteral("\\\\.\\COM4"));

    printScheduler->addPrintingBed('A',"/home/hix/Desktop");

    printScheduler->printFilePath = "/home/hix/printFilePath";

//    printScheduler->receiveFromQmlBedSetBedPath('A',"/");
//    printScheduler->receiveFromQmlBedSetBedPath('A',"/home/pi");
    printScheduler->receiveFromQmlBedSetBedPath('A');


    printScheduler->start();

    return app.exec();

}

