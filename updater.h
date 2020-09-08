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

public slots:
    void requestFinished(QNetworkReply* reply);
    void MCUFirmwareUpdateFinished();

    void checkUpdate();
    void update();

signals:
    void updateAvailable();
    void updateNotAvailable();
    void updateFinished();
    void updateError();

    void updateMCUFirmware(QString path);

private:
    QString _url;
    QString _downloadUrl;

    const QString _binName = "KinematicFW.binary";
    const QString _shName = "update.sh";
    const QString _zipName = "files.zip";
    const QString _verName = "version.json";

    SWRequestType _requestType = SWRequestType::NONE;

    std::condition_variable _cv;
    std::mutex _cv_m;

    bool _requestAvailable = true;
    bool _MCUFirmwareUpdateAvailable = false;

    bool _MCUFirmwareUpdateFinished = false;

    bool _networkError = false;

    std::future<void> _future;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

};

#endif // UPDATER_H