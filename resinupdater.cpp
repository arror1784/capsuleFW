#include "resinupdater.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QByteArray>

#include "printsetting.h"
#include "resinsetting.h"

ResinUpdater::ResinUpdater()
//    : _url("http://10.42.0.1:8000/resin/download/")
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished,this, &ResinUpdater::requestFinished);
}

void ResinUpdater::checkUpdate()
{
    _requestType = ResinRequestType::UPDATE;
    request.setUrl(QUrl("https://services.hix.co.kr/resin/update/"));
    manager->get(request);
}

void ResinUpdater::update()
{
    _requestType = ResinRequestType::DOWNLOAD_ALL;
    request.setUrl(QUrl("https://services.hix.co.kr/resin/download/"));
    manager->get(request);
}

void ResinUpdater::requestFinished(QNetworkReply* reply)
{
    if (reply->error()) {
        emit updateError();
        qDebug() << reply->errorString();
        return;
    }
    qDebug() << reply->url();
    QByteArray answer = reply->readAll();
//    reply->
//    qDebug() << answer;
    switch (_requestType) {
        case ResinRequestType::UPDATE:
            {
                QJsonDocument jd = QJsonDocument::fromJson(answer);
                QJsonArray ja = jd.array();

                QJsonArray resinList = PrintSetting::GetInstance()->getResinList();

                if(resinList.size() != ja.size()){
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
        case ResinRequestType::DOWNLOAD:
            break;
        case ResinRequestType::DOWNLOAD_ALL:
            {
                QJsonDocument jd = QJsonDocument::fromJson(answer);
                QJsonArray ja = jd.array();

                QJsonArray sl;

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
        case ResinRequestType::NONE:
            break;
    }
}
