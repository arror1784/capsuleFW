#include "resinupdater.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QByteArray>

#include "printersetting.h"
#include "resinsetting.h"

ResinUpdater::ResinUpdater()
//    : _url("http://10.42.0.1:8000/resin/download/")
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished,this, &ResinUpdater::requestFinished);
    updateVersionInFo();
    checkUpdate();
}

void ResinUpdater::checkUpdate()
{
    _requestType = ResinRequestType::UPDATE;
    request.setUrl(QUrl("https://services.hix.co.kr/resin/update/C10"));
    manager->get(request);
}

void ResinUpdater::update()
{
    _requestType = ResinRequestType::DOWNLOAD_ALL;
    request.setUrl(QUrl("https://services.hix.co.kr/resin/download/C10"));
    manager->get(request);
}

QString ResinUpdater::version()
{
    return _updateTime.toString("dd/MM/yyyy");
}

QString ResinUpdater::lastestVersion()
{
    return _lastestUpdateTime.toString("dd/MM/yyyy");
}

void ResinUpdater::updateVersionInFo()
{
    QJsonArray resinList = PrinterSetting::getInstance().getResinList();

    for(int i = 0;i < resinList.size();i++) {
        QString mID = resinList[i].toString();
        ResinSetting rs(mID);

        QDateTime last = QDateTime::fromString(rs.getResinSetting("last_update").toString(),"MM/dd/yyyy, hh:mm:ss");
        qDebug() << last << rs.getResinSetting("last_update").toString();
        if(last > _updateTime){
            _updateTime = last;
        }
    }
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
                QJsonArray resinList = PrinterSetting::getInstance().getResinList();
                bool upAvailable = false;

                if(resinList.size() != ja.size()){
                    upAvailable = true;
                }

                for(int i = 0;i < ja.size();i++) {
                    QJsonObject jo = ja[i].toObject();
                    QString mID = jo.keys()[0];
                    QString lastUpdate = jo.value(mID).toString();

                    QDateTime last = QDateTime::fromString(lastUpdate,"MM/dd/yyyy, hh:mm:ss");
                    if(last > _lastestUpdateTime){
                        _lastestUpdateTime = last;
                    }

                    if(!resinList.contains(mID)){
                        upAvailable = true;
                    }else{
                        ResinSetting rs(mID);
                        if(rs.getResinSetting("last_update").toString() != lastUpdate){
                            upAvailable = true;
                        }
                    }
//                    qDebug() << ja[i];
                }
                if(upAvailable){
                    emit updateAvailable();
                }else{
                    emit updateNotAvailable();
                }
            }
            break;
        case ResinRequestType::DOWNLOAD:
            break;
        case ResinRequestType::DOWNLOAD_ALL:
            {
                QJsonDocument jd = QJsonDocument::fromJson(answer);
                QJsonObject ja = jd.object();

                QJsonArray sl;

                QJsonArray resinList = PrinterSetting::getInstance().getResinList();

                for (int i = 0; i < resinList.size();i++) {
                    ResinSetting rs(resinList[i].toString());
                    rs.removeFile();
                }

                foreach(const QString& key, ja.keys()){
                    QString mID = key;
                    sl.append(mID);

                    ResinSetting rs(mID);
                    rs.setResinSetting(ja.value(key).toObject());
                }

                PrinterSetting::getInstance().setResinList(sl);

                updateVersionInFo();
                emit updateFinished();
            }
            break;
        case ResinRequestType::NONE:
            break;
    }
}
