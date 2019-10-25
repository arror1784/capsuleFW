#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>

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

    ctx->setContextProperty("scheduler",printScheduler);

    engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
//    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


//    printScheduler->addSerialPort(QStringLiteral("/dev/ttyAMA0"));
    printScheduler->addSerialPort();
//    printScheduler->addSerialPort(QStringLiteral("\\\\.\\COM4"));



//    printScheduler->addPrintingBed('A',"/home/pi/Desktop");
    printScheduler->addPrintingBed('A',"/");
    printScheduler->printFilePath = "/home/pi/printFilePath";
//    printScheduler->printFilePath = "/home/pi/printFilePath";

//    printScheduler->receiveFromQmlBedSetBedPath('A',"/");
//    printScheduler->receiveFromQmlBedSetBedPath('A',"/home/pi");
//    printScheduler->receiveFromQmlBedSetBedPath('A');


    printScheduler->start();

    return app.exec();

}

