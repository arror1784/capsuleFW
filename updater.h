#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QNetworkRequest>
#include <QByteArray>
#include <future>
#include <condition_variable>
#include <thread>
#include "common.h"

enum class SWRequestType
{
    UPDATE_CHECK,
    DOWNLOAD_LIST,
    DOWNLOAD_SH,
    DOWNLOAD_ZIP,
    DOWNLOAD_BIN,
    DOWNLOAD_VER,
    DOWNLOAD_ALL,
    NONE
};

class QNetworkAccessManager;
class QNetworkReply;
class Updater : public QObject
{
    Q_OBJECT
public:
    Updater();

    void saveAsFile(QString name,QByteArray ba);
    void downloadBin();
    void downloadSH();
    void downloadZIP();
    void downloadVER();
    void downloadLIST();

    int waitForRequest();
    void waitForMCUFirmwareUpdate();

signals:
    void updateNotice(QString state);

    void sendVersion(QString version);
    void sendLastestVersion(QString version);

    void updateMCUFirmware(QString path);

public slots:
    void getVersion();
    void getLastestVersion();

    void requestFinished(QNetworkReply* reply);
    void MCUFirmwareUpdateFinished();

    void checkUpdate();
    void update();


#ifdef MCU_UPDATE_TEST
    void MCUUpdate(QString path);
#endif

private:
    QString _url;
    QString _downloadUrl;

    QString _lastestVersion = "";

    const QString _binName = "KinematicFW.binary";
    const QString _shName = "update.sh";
    const QString _zipName = "files.zip";
    const QString _verName = "version.json";

    SWRequestType _requestType = SWRequestType::NONE;

    std::condition_variable _cv;
    std::mutex _cv_m;

    std::condition_variable _cv_mcu;
    std::mutex _cv_mcu_m;

    bool _requestAvailable = true;
    bool _MCUFirmwareUpdateAvailable = false;

    bool _MCUFirmwareUpdateFinished = false;

    bool _networkError = false;

    std::future<void> _future;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

};

#endif // UPDATER_H
