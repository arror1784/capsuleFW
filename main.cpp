﻿#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QJsonArray>
#include <QTextCodec>

#include <QNetworkInterface>
#include <QList>

#include <QThread>
#include <QQmlContext>
#include <QQuickView>

#include "bedserialport.h"
#include "bedcontrol.h"
#include "printscheduler.h"
#include "printsetting.h"
#include "logger.h"
//#include "networkcontrol.h"
#include "websocketclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    PrintScheduler* printScheduler = new PrintScheduler();

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();

//    NetworkControl nc;
//    WebSocketClient wsc(QUrl(QStringLiteral("ws://localhost:8000/ws/printer")));

    ctx->setContextProperty("scheduler",printScheduler);
//    ctx->setContextProperty("nc",&nc);

    engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    if(!printScheduler->addSerialPort()){
        printScheduler->addPrintingBed('A',"/");
//        printScheduler->addPrintingBed('A',"/home/hix/Desktop");
        printScheduler->printFilePath = "/home/pi/printFilePath";
//        printScheduler->printFilePath = "/home/hix/printFilePath";

        printScheduler->start();
        
    }else{
        Logger::GetInstance()->write("port open error");
        qDebug() << "port open error";

        return app.exec();
    }

    return app.exec();
}
