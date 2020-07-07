#ifndef RESINUPDATER_H
#define RESINUPDATER_H

#include <QObject>
#include <QNetworkRequest>
//#include <QNetworkReply>

enum class RequestType
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
    ResinUpdater();

public slots:
    void requestFinished(QNetworkReply* reply);

    void checkUpdate();
    void update();

signals:
    void updateAvailable();
    void updateNotAvailable();
    void updateFinished();

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;

    RequestType requestType = RequestType::NONE;
};

#endif // RESINUPDATER_H
