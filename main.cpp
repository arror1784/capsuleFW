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

#include "bedserialport.h"
#include "bedcontrol.h"
#include "printscheduler.h"
#include "printsetting.h"
#include "logger.h"
#include "networkcontrol.h"
#include "websocketclient.h"
#include "resinupdater.h"
#include "filevalidator.h"
#include "updater.h"
#include "version.h"

#include "zip/zip.h"

#include "kinetimecalc.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    PrintScheduler* printScheduler = new PrintScheduler();

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();

    NetworkControl nc;
    ResinUpdater ru;
    Updater up;

    QObject::connect(&up,&Updater::updateMCUFirmware,printScheduler,&PrintScheduler::receiveFromUpdaterFirmUpdate);
    QObject::connect(printScheduler,&PrintScheduler::MCUFirmwareUpdateFinished,&up,&Updater::MCUFirmwareUpdateFinished);

    qmlRegisterType<FileValidator>("App", 1, 0, "FileValidator");

    ctx->setContextProperty("scheduler",printScheduler);
    ctx->setContextProperty("nc",&nc);
    ctx->setContextProperty("resinUpdater",&ru);
    ctx->setContextProperty("SWUpdater",&up);

//    qDebug() << "KineCalc : " << KineTimeCalc::calcTRMoveTime(500,0,500,-500,5);
//    qDebug() << "verion " << Version::getInstance().getVersion();

//    engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    printScheduler->start();

    return app.exec();
}
