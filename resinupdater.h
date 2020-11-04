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
    void updateNotice(QString state);

    void sendVersion(QString version);
    void sendLastestVersion(QString version);

public slots:
    void requestFinished(QNetworkReply* reply);

    void checkUpdate();
    void update();

    void getVersion();
    void getLastestVersion();


private:
    void updateVersionInFo();
    QNetworkAccessManager *manager;
    QNetworkRequest request;

    ResinRequestType _requestType = ResinRequestType::NONE;

    QUrl _url;

    QDateTime _updateTime;
    QDateTime _lastestUpdateTime;
    PrintScheduler* _printScheduler;
};

#endif // RESINUPDATER_H
