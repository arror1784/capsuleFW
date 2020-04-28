#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QJsonArray>
#include <QTextCodec>

#include <QThread>
#include <QQmlContext>
#include <QQuickView>

#include "bedserialport.h"
#include "bedcontrol.h"
#include "printscheduler.h"
#include "printsetting.h"
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
    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

//    qDebug() << "sjighnkjsdfsdf" << PrintSetting::GetInstance()->getPrintSetting("led_offset").toDouble();
//    PrintSetting::GetInstance()->setPrintSetting("led_offset",100.0);
//    PrintSetting::GetInstance()->saveFile();
//    qDebug() << PrintSetting::GetInstance()->getPrintSetting("led_offset").toInt();

    if(!printScheduler->addSerialPort()){
        printScheduler->addPrintingBed('A',"/");
//        printScheduler->addPrintingBed('A',"/home/jsh/Desktop");
        printScheduler->printFilePath = "/home/pi/printFilePath";
//        printScheduler->printFilePath = "/home/jsh/printFilePath";

        printScheduler->start();
    }else{
        Logger::GetInstance()->write("port open error");
        qDebug() << "port open error";
        return app.exec();
    }
    return app.exec();
}
