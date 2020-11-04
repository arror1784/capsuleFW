#include <QGuiApplication>
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
#include "updateconnector.h"

#include "kinetimecalc.h"
#include "FilesystemModel.h"

#include "wpa_ctrl/wpa_ctrl.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext* ctx = engine.rootContext();
    qDebug() << "main" << QThread::currentThread();

//    WPA wpa;
    NetworkControl nc;
    QmlConnecter connecter;
    UpdateConnector up;
    SchedulerThread backThread(engine,connecter,up);

    backThread.start();

    qmlRegisterType<WifiInfo>("App", 1, 0, "WifiInfo");
    qmlRegisterType<Hix::QML::FilesystemModel>("App", 1, 0, "HixFilesystemModel");

    ctx->setContextProperty("nc",&nc);
    ctx->setContextProperty("connection",&connecter);
//    ctx->setContextProperty("wifi",&wpa);
    ctx->setContextProperty("updater",&up);

//    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
//    engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    return app.exec();
}
