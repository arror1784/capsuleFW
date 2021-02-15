﻿#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>

#include <QNetworkInterface>

#include <QQmlContext>

#include <QApplication>
#include <QDesktopWidget>

#include "wpa.h"

#include "schedulerthread.h"
#include "logger.h"
#include "networkcontrol.h"
#include "filevalidator.h"
#include "qmlconnecter.h"
#include "updateconnector.h"

#include "kinetimecalc.h"
#include "FilesystemModel.h"
#include "zipcontrol.h"

#include "wpa_ctrl/wpa_ctrl.h"
#include "VKeyboard/keyboardwidget.h"
#include "printimage.h"
#include "printimagecontrol.h"
#include "c10printimage.h"
#include "l10printimage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication application (argc, argv);
//    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext* ctx = engine.rootContext();
    qDebug() << "main" << QThread::currentThread();

    WPA wpa;
    KeyboardWidget keyboardWidget;
    NetworkControl nc;
    QmlConnecter connecter;
    UpdateConnector up;
    PrintImage printImage;

    PrintImageControl *pic;
    L10ImageProvider l10ip;
    if(ProductSetting::getInstance().product == ProductType::C10){
        pic = new C10PrintImage;
    }else if(ProductSetting::getInstance().product == ProductType::L10){
        pic = new L10PrintImage(&l10ip);
    }
    SchedulerThread backThread(engine,connecter,up,pic);
    backThread.start();

    qmlRegisterType<WifiInfo>("App", 1, 0, "WifiInfo");
    qmlRegisterType<Hix::QML::FilesystemModel>("App", 1, 0, "HixFilesystemModel");
    qmlRegisterType<ZipControl>("App", 1, 0, "ZipControl");

    engine.addImageProvider(QLatin1String("L10"), &l10ip);
    ctx->setContextProperty("wifi",&wpa);
    ctx->setContextProperty("nc",&nc);
    ctx->setContextProperty("connection",&connecter);
    ctx->setContextProperty("updater",&up);
    ctx->setContextProperty("keyboardWidget",&keyboardWidget);
    ctx->setContextProperty("printImage",pic);
//    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
//    engine.load(QUrl(QStringLiteral("qrc:/Qml/svgWindow.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    return application.exec();
//    return app.exec();
}
