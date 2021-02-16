#ifndef RESINUPDATER_H
#define RESINUPDATER_H

#include <QObject>
#include <QNetworkRequest>
#include <QDateTime>
#include <QNetworkReply>
#include <printscheduler.h>

enum class ResinRequestType
{
    UPDATE,
    DOWNLOAD,
    DOWNLOAD_ALL,
    NONE
};

class QNetworkAccessManager;
class QNetworkReply;
class ResinUpdater : public QObject
{
    Q_OBJECT
public:
    ResinUpdater(PrintScheduler *sched);

signals:
    void updateNotice(QString state,QString mode);

    void sendVersion(QString version);
    void sendLastestVersion(QString version);

public slots:
    void requestFinished(QNetworkReply* reply);

    void checkUpdate();
    void checkUpdateUSB(QString path);
    void update();
    void updateUSB(QString path);

    void getVersion();

private:
    void updateVersionInFo();
    QNetworkAccessManager *manager;
    QNetworkRequest request;

    ResinRequestType _requestType = ResinRequestType::NONE;

    QUrl _url;

    QDateTime _updateTime;
    PrintScheduler* _printScheduler;

    QUrl _updateUrl;
    QUrl _downloadUrl;

};

#endif // RESINUPDATER_H
