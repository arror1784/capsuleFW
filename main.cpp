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

#include <wpa.h>

#include "bedserialport.h"
#include "bedcontrol.h"
#include "printscheduler.h"
#include "schedulerthread.h"
#include "printersetting.h"
#include "logger.h"
#include "networkcontrol.h"
#include "websocketclient.h"
#include "resinupdater.h"
#include "filevalidator.h"
#include "updater.h"
#include "version.h"
#include "qmlconnecter.h"

#include "kinetimecalc.h"
#include "FilesystemModel.h"

#include "wpa_ctrl/wpa_ctrl.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //QQmlContext* ctx = engine.rootContext();
    //qDebug() << "main" << QThread::currentThread();

    //QmlConnecter connecter;
    //SchedulerThread backThread(engine,connecter);

    WPA wpa;
    ctx->setContextProperty("wifi",&wpa);

    backThread.start();

    qmlRegisterType<WifiInfo>("App", 1, 0, "WifiInfo");

    ctx->setContextProperty("connection",&connecter);
    ctx->setContextProperty("wifi",&wpa);

    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
