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

#include "kinetimecalc.h"

#include "wpa_ctrl/wpa_ctrl.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    PrintScheduler* printScheduler = new PrintScheduler();

    QQmlApplicationEngine engine;

    SchedulerThread backThread(engine);

    QQmlContext* ctx = engine.rootContext();

//    NetworkControl nc;
//    ResinUpdater ru(printScheduler);
//    Updater up;
//    WPA wpa;

//    QObject::connect(&up,&Updater::updateMCUFirmware,printScheduler,&PrintScheduler::receiveFromUpdaterFirmUpdate);
//    QObject::connect(printScheduler,&PrintScheduler::MCUFirmwareUpdateFinished,&up,&Updater::MCUFirmwareUpdateFinished);

    qmlRegisterType<FileValidator>("App", 1, 0, "FileValidator");
    qmlRegisterType<WifiInfo>("App", 1, 0, "WifiInfo");

//    ctx->setContextProperty("scheduler",printScheduler);
//    ctx->setContextProperty("nc",&nc);
//    ctx->setContextProperty("resinUpdater",&ru);
//    ctx->setContextProperty("SWUpdater",&up);
//    ctx->setContextProperty("wifi",&wpa);

//    std::cout << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;

//    qDebug() << "KineCalc : " << KineTimeCalc::calcTRMoveTime(500,0,500,-500,5);

    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

//    printScheduler->start();

    return app.exec();
}
