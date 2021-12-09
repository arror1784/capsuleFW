#include "resinsetting.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>
#include <stdexcept>

using namespace Hix::Common;

const QString _resinPath = "/opt/capsuleFW/resin/";

ResinSetting::ResinSetting(QString resin) : Json::JsonSetting(_resinPath + resin + ".json")
//    ,_layerHeight(layerHeight)
{

}

ResinSetting::~ResinSetting()
{

}

void ResinSetting::parse()
{
    try {
        for(auto &i : _object.keys()){
            if(i == "last_update"){
                lastUpdate = Hix::Common::Json::getValue<QString>(_object,"last_update");
            }else if(i == "visible"){
                if(!Hix::Common::Json::tryGetValue<bool>(_object,"visible",visible))
                    visible = true;
            }else{
                resinInfo ri;
                QJsonObject jo = Hix::Common::Json::getValue<QJsonObject>(_object,i);

                ri.resinLedOffset = Hix::Common::Json::getValue<double>(jo,"led_offset");
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

                if(!Hix::Common::Json::tryGetValue<int>(jo,"pixel_contraction",ri.pixelContraction))
                    ri.pixelContraction = 0;

                if(!Hix::Common::Json::tryGetValue<float>(jo,"ymult",ri.ymult))
                    ri.ymult = 1.0;

                resinList.insert(i,ri);
            }
        }
    } catch (std::runtime_error &e) {
        qDebug() << e.what();
    }

}

QString ResinSetting::serialize()
{
    save();

    QJsonDocument doc(_object);

    return doc.toJson();
}

void ResinSetting::save()
{
    QJsonObject jo;
    QFile saveFile(_path);

    Json::setValue<QString>(jo,"last_update",lastUpdate);
    Json::setValue<bool>(jo,"visible",visible);

    for(auto &i : resinList.keys()){
        QJsonObject resinObject;

        Hix::Common::Json::setValue<double>(resinObject,"led_offset",resinList[i].resinLedOffset);
        Hix::Common::Json::setValue<double>(resinObject,"layer_height",resinList[i].layerHeight);

        Hix::Common::Json::setValue<int>(resinObject,"bed_curing_layer",resinList[i].bedCuringLayer);
        Hix::Common::Json::setValue<int>(resinObject,"curing_time",resinList[i].curingTime);
        Hix::Common::Json::setValue<int>(resinObject,"z_hop_height",resinList[i].zHopHeight);
        Hix::Common::Json::setValue<int>(resinObject,"max_speed",resinList[i].maxSpeed);
        Hix::Common::Json::setValue<int>(resinObject,"init_speed",resinList[i].initSpeed);
        Hix::Common::Json::setValue<int>(resinObject,"up_accel_speed",resinList[i].upAccelSpeed);
        Hix::Common::Json::setValue<int>(resinObject,"up_decel_speed",resinList[i].upDecelSpeed);
        Hix::Common::Json::setValue<int>(resinObject,"down_accel_speed",resinList[i].downAccelSpeed);
        Hix::Common::Json::setValue<int>(resinObject,"down_decel_speed",resinList[i].downDecelSpeed);
        Hix::Common::Json::setValue<int>(resinObject,"bed_curing_time",resinList[i].bedCuringTime);
        Hix::Common::Json::setValue<int>(resinObject,"layer_delay",resinList[i].layerDelay);
        Hix::Common::Json::setValue<int>(resinObject,"material",resinList[i].material);

        Hix::Common::Json::setValue<int>(resinObject,"pixel_contraction",resinList[i].pixelContraction);
        Hix::Common::Json::setValue<float>(resinObject,"ymult",resinList[i].ymult);

        Hix::Common::Json::setValue<QJsonObject>(jo,i,resinObject);
    }

    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "save file open error";
    }
    _object = jo;
    QJsonDocument saveDoc(jo);

    saveFile.write(saveDoc.toJson());
}

bool ResinSetting::removeFile()
{
    QFile reFile(_path);
    reFile.setFileName(_path);
    if(reFile.exists()){
        if(reFile.remove()){
            qDebug() << "file remove " << _path;
            return true;
        }else{
            qDebug() << "cannot remove this file " << _path;
            return false;
        }
    }else{
        qDebug() << "cannot remove this file : does not exist " << _path;
        return false;
    }
}

bool ResinSetting::createFile()
{
    QFile loadFile(_path);
    if(!loadFile.open(QIODevice::ReadWrite)){
        qDebug() << "Could not open json file to ReadWrite " << _path;
        qDebug() << loadFile.errorString();
        return false;
    }else{
        return true;
    }
}
