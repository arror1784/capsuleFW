#include "resinupdater.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QVector>

#include <QByteArray>

#include "printersetting.h"
#include "resinsetting.h"
#include "common/jsonutil.h"
#include "zip/zip.h"

ResinUpdater::ResinUpdater(PrintScheduler *sched) : _printScheduler(sched)
//    : _url("http://10.42.0.1:8000/resin/download/")
{
    manager = new QNetworkAccessManager();
    QObject::connect(manager, &QNetworkAccessManager::finished,this, &ResinUpdater::requestFinished);
    updateVersionInFo();
    checkUpdate();
}

void ResinUpdater::checkUpdate()
{
    _requestType = ResinRequestType::UPDATE;
    request.setUrl(QUrl("https://services.hix.co.kr/resin/update/C10"));
    manager->get(request);
}

void ResinUpdater::checkUpdateUSB(QString path)
{
    auto spath = path.toStdString();

    try {

        miniz_cpp::zip_file file(spath);
        auto testValue = file.testzip();
        if(!testValue.first){
            emit updateNotice("error","usb");
            return;
        }
        if(!file.has_file("USB")){
            emit updateNotice("error","usb");
        }
        if(!file.has_file("RESIN")){
            emit updateNotice("error","usb");
        }
        QJsonDocument jd = QJsonDocument::fromJson(QByteArray::fromStdString(file.read("material_list.json")));
        QJsonArray ja = jd.array();

        QVector<QString> resinList = _printScheduler->_printerSetting.materialList;

        bool upAvailable = false;

        if(resinList.size() != ja.size()){
            upAvailable = true;
        }
        QDateTime lastestUpdateTime;
        for(int i = 0;i < ja.size();i++) {
            QJsonObject jo = ja[i].toObject();
            QString mID = jo.keys()[0];
            QString lastUpdate = jo.value(mID).toString();

            QDateTime last = QDateTime::fromString(lastUpdate,"MM/dd/yyyy, hh:mm:ss");
            if(last > lastestUpdateTime){
                lastestUpdateTime = last;
            }

            if(!resinList.contains(mID)){
                upAvailable = true;
            }else{
                ResinSetting rs(mID);
                rs.parse();
                if(rs.lastUpdate != lastUpdate){
                    upAvailable = true;
                }
            }
        }
        if(upAvailable){
            emit updateNotice("available","usb");
        }else{
            emit updateNotice("notAvailable","usb");
        }
        emit sendLastestVersion(lastestUpdateTime.toString("dd/MM/yyyy"));

    } catch (std::exception e) {
        emit updateNotice("error","usb");
    }
}

void ResinUpdater::update()
{
    _requestType = ResinRequestType::DOWNLOAD_ALL;
    request.setUrl(QUrl("https://services.hix.co.kr/resin/download/C10"));
    manager->get(request);
}

void ResinUpdater::updateUSB(QString path)
{
    auto spath = path.toStdString();

    try {
        miniz_cpp::zip_file file(spath);
        auto testValue = file.testzip();
        if(!testValue.first){
            emit updateNotice("error","usb");
            return;
        }
        QJsonDocument jd = QJsonDocument::fromJson(QByteArray::fromStdString(file.read("material_list.json")));
        auto ja = jd.array();

        QVector<QString> sl;

        QVector<QString> resinList = _printScheduler->_printerSetting.materialList;

        //resin remove code
        for (int i = 0; i < resinList.size();i++) {
            ResinSetting rs(resinList[i]);
            rs.removeFile();
        }

        foreach(const auto& key, ja){
            QString mID = key.toObject().keys()[0];
            sl.append(mID);
            //To do add resin create code
            ResinSetting rs(mID);
            rs.createFile();

            QJsonDocument jd = QJsonDocument::fromJson(QByteArray::fromStdString(file.read(mID.toStdString()+".json")));
            QJsonObject object = jd.object();

            for(auto &i : object.keys()){
                if(i == "last_update"){
                    rs.lastUpdate = Hix::Common::Json::getValue<QString>(object,"last_update");
                }else{
                    ResinSetting::resinInfo ri;
                    QJsonObject jo = Hix::Common::Json::getValue<QJsonObject>(object,i);

                    ri.resinLedOffset = Hix::Common::Json::getValue<double>(jo,"led_offset");
                    ri.contractionRatio = Hix::Common::Json::getValue<double>(jo,"contraction_ratio");
                    ri.layerHeight = Hix::Common::Json::getValue<double>(jo,"layer_height");

                    ri.bedCuringLayer = Hix::Common::Json::getValue<int>(jo,"bed_curing_layer");
                    ri.curingTime = Hix::Common::Json::getValue<int>(jo,"curing_time");
                    ri.zHopHeight = Hix::Common::Json::getValue<int>(jo,"z_hop_height");
                    ri.maxSpeed = Hix::Common::Json::getValue<int>(jo,"max_speed");
                    ri.initSpeed = Hix::Common::Json::getValue<int>(jo,"init_speed");
                    ri.upAccelSpeed = Hix::Common::Json::getValue<int>(jo,"up_accel_speed");
                    ri.upDecelSpeed = Hix::Common::Json::getValue<int>(jo,"up_decel_speed");
                    ri.downAccelSpeed = Hix::Common::Json::getValue<int>(jo,"down_accel_speed");
                    ri.downDecelSpeed = Hix::Common::Json::getValue<int>(jo,"down_decel_speed");
                    ri.bedCuringTime = Hix::Common::Json::getValue<int>(jo,"bed_curing_time");
                    ri.layerDelay = Hix::Common::Json::getValue<int>(jo,"layer_delay");
                    ri.material = Hix::Common::Json::getValue<int>(jo,"material");

                    rs.resinList.insert(i,ri);
                }
            }
            rs.save();
        }

        _printScheduler->_printerSetting.materialList = sl;
        _printScheduler->_printerSetting.save();

        updateVersionInFo();
        emit updateNotice("finish","usb");

    } catch (std::exception e) {
        emit updateNotice("error","usb");
    }
    //testzip
    //check version
    //update by USB
}
void ResinUpdater::getVersion()
{
    emit sendVersion(_updateTime.toString("dd/MM/yyyy"));
}

void ResinUpdater::updateVersionInFo()
{
//    QVector<QString>& resinList = _printScheduler->_printerSetting.enableMaterialList;

//    if(resinList.empty()){
    QVector<QString> resinList = _printScheduler->_printerSetting.materialList;
//    }
    QDateTime currentTime;

    for(int i = 0;i < resinList.size();i++) {
        QString mID = resinList[i];
        ResinSetting rs(mID);
        rs.parse();
        QDateTime last = QDateTime::fromString(rs.lastUpdate,"MM/dd/yyyy, hh:mm:ss");
        if(last > currentTime){
            currentTime = last;
        }
        _updateTime = currentTime;
        emit sendVersion(_updateTime.toString("dd/MM/yyyy"));
    }
}

void ResinUpdater::requestFinished(QNetworkReply* reply)
{
    if (reply->error()) {
        emit updateNotice("error","network");
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
                QVector<QString> resinList = _printScheduler->_printerSetting.materialList;
                bool upAvailable = false;
                QDateTime lastestUpdateTime;
                if(resinList.size() != ja.size()){
                    upAvailable = true;
                }

                for(int i = 0;i < ja.size();i++) {
                    QJsonObject jo = ja[i].toObject();
                    QString mID = jo.keys()[0];
                    QString lastUpdate = jo.value(mID).toString();

                    QDateTime last = QDateTime::fromString(lastUpdate,"MM/dd/yyyy, hh:mm:ss");
                    if(last > lastestUpdateTime){
                        lastestUpdateTime = last;
                    }

                    if(!resinList.contains(mID)){
                        upAvailable = true;
                    }else{
                        ResinSetting rs(mID);
                        rs.parse();
                        if(rs.lastUpdate != lastUpdate){
                            upAvailable = true;
                        }
                    }
//                    qDebug() << ja[i];
                }
                if(upAvailable){
                    emit updateNotice("available","network");
                }else{
                    emit updateNotice("notAvailable","network");
                }
                emit sendLastestVersion(lastestUpdateTime.toString("dd/MM/yyyy"));
            }
            break;
        case ResinRequestType::DOWNLOAD:
            break;
        case ResinRequestType::DOWNLOAD_ALL:
            {
                QJsonDocument jd = QJsonDocument::fromJson(answer);
                QJsonObject ja = jd.object();

                QVector<QString> sl;

                QVector<QString> resinList = _printScheduler->_printerSetting.materialList;

                //resin remove code
                for (int i = 0; i < resinList.size();i++) {
                    ResinSetting rs(resinList[i]);
                    rs.removeFile();
                }

                foreach(const QString& key, ja.keys()){
                    QString mID = key;
                    sl.append(mID);
                    //To do add resin create code
                    ResinSetting rs(mID);
                    rs.createFile();
                    QJsonObject object = ja.value(key).toObject();

                    for(auto &i : object.keys()){
                        if(i == "last_update"){
                            rs.lastUpdate = Hix::Common::Json::getValue<QString>(object,"last_update");
                        }else{
                            ResinSetting::resinInfo ri;
                            QJsonObject jo = Hix::Common::Json::getValue<QJsonObject>(object,i);

                            ri.resinLedOffset = Hix::Common::Json::getValue<double>(jo,"led_offset");
                            ri.contractionRatio = Hix::Common::Json::getValue<double>(jo,"contraction_ratio");
                            ri.layerHeight = Hix::Common::Json::getValue<double>(jo,"layer_height");

                            ri.bedCuringLayer = Hix::Common::Json::getValue<int>(jo,"bed_curing_layer");
                            ri.curingTime = Hix::Common::Json::getValue<int>(jo,"curing_time");
                            ri.zHopHeight = Hix::Common::Json::getValue<int>(jo,"z_hop_height");
                            ri.maxSpeed = Hix::Common::Json::getValue<int>(jo,"max_speed");
                            ri.initSpeed = Hix::Common::Json::getValue<int>(jo,"init_speed");
                            ri.upAccelSpeed = Hix::Common::Json::getValue<int>(jo,"up_accel_speed");
                            ri.upDecelSpeed = Hix::Common::Json::getValue<int>(jo,"up_decel_speed");
                            ri.downAccelSpeed = Hix::Common::Json::getValue<int>(jo,"down_accel_speed");
                            ri.downDecelSpeed = Hix::Common::Json::getValue<int>(jo,"down_decel_speed");
                            ri.bedCuringTime = Hix::Common::Json::getValue<int>(jo,"bed_curing_time");
                            ri.layerDelay = Hix::Common::Json::getValue<int>(jo,"layer_delay");
                            ri.material = Hix::Common::Json::getValue<int>(jo,"material");

                            rs.resinList.insert(i,ri);
                        }
                    }
                    rs.save();
                }

                _printScheduler->_printerSetting.materialList = sl;
                _printScheduler->_printerSetting.save();

                updateVersionInFo();
                emit updateNotice("finish","network");
            }
            break;
        case ResinRequestType::NONE:
            break;
    }
}
