#include "resinupdater.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "printsetting.h"
#include "resinsetting.h"

ResinUpdater::ResinUpdater()
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished,this, &ResinUpdater::requestFinished);
}

void ResinUpdater::checkUpdate()
{
    requestType = RequestType::UPDATE;
    request.setUrl(QUrl("http://10.42.0.1:8000/resin/update/"));
    manager->get(request);
}

void ResinUpdater::update()
{
    requestType = RequestType::DOWNLOAD_ALL;
    request.setUrl(QUrl("http://10.42.0.1:8000/resin/download/"));
    manager->get(request);
}

void ResinUpdater::requestFinished(QNetworkReply* reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    qDebug() << reply->url();
    QString answer = reply->readAll();
//    qDebug() << answer;
    switch (requestType) {
        case RequestType::UPDATE:
            {
                QJsonDocument jd = QJsonDocument::fromJson(answer.toUtf8());
                QJsonArray ja = jd.array();

                QJsonArray resinList = PrintSetting::GetInstance()->getResinList();

                if(resinList.size() - 1 != ja.size()){
                    qDebug() << "update available 1";
                    emit updateAvailable();
                    return;
                }

                for(int i = 0;i < ja.size();i++) {
                    QString mID = ja[i].toObject()["fields"].toObject()["M_id"].toString();
                    QString lastUpdate = ja[i].toObject()["fields"].toObject()["last_update"].toString();
                    if(!resinList.contains(mID)){
                        qDebug() << "update available 2";
                        emit updateAvailable();
                        return;
                    }
                    ResinSetting rs(mID);
                    if(rs.getResinSetting("last_update").toString() != lastUpdate){
                        qDebug() << "update available 3";
                        emit updateAvailable();
                        return;
                    }
//                    qDebug() << ja[i];
                }
                qDebug() << "update not available";
                emit updateNotAvailable();
//                update();
            }
            break;
        case RequestType::DOWNLOAD:
            break;
        case RequestType::DOWNLOAD_ALL:
            {
                QJsonDocument jd = QJsonDocument::fromJson(answer.toUtf8());
                QJsonArray ja = jd.array();

                QJsonArray sl;
                sl.append("custom");

                QJsonArray resinList = PrintSetting::GetInstance()->getResinList();

                for(int i = 0;i < ja.size();i++) {
                    QString mID = ja[i].toObject()["fields"].toObject()["M_id"].toString();
                    QString lastUpdate = ja[i].toObject()["fields"].toObject()["last_update"].toString();
                    QJsonObject jo = ja[i].toObject()["fields"].toObject();
                    sl.append(mID);

                    ResinSetting rs(mID);
                    rs.setResinSetting(jo);
//                    qDebug() << ja[i];
                }

                PrintSetting::GetInstance()->setResinList(sl);
                emit updateFinished();
            }
            break;
        case RequestType::NONE:
            break;
    }
}
