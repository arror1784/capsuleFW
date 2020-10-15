#include "printersetting.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

using namespace Hix::Common;

constexpr auto _filePath = "/opt/capsuleFW/capsuleSetting.json";

PrinterSetting::PrinterSetting() : Hix::Common::Json::JsonSetting (_filePath)
{

}

void PrinterSetting::parse()
{
    QJsonObject UVTimeSpendObject = Json::getValue<QJsonObject>(_object,"UV_time_spend");
    for(auto &i : UVTimeSpendObject.keys()){
        UVTimeSpend.insert(i,Json::getValue<int>(UVTimeSpendObject,i));
    }
    QJsonObject motorTimeSpendObject = Json::getValue<QJsonObject>(_object,"motor_time_spend");
    for(auto &i : motorTimeSpendObject.keys()){
        UVTimeSpend.insert(i,Json::getValue<int>(motorTimeSpendObject,i));
    }

    materialList = Json::getValueArray<QString>(_object,"material_list");
    enableMaterialList = Json::getValueArray<QString>(_object,"enable_material_list");

    defaultHeight = Json::getValue<int>(_object,"default_height");
    heightOffset = Json::getValue<int>(_object,"height_offset");
    ledOffset = Json::getValue<double>(_object,"led_offset");
}

void PrinterSetting::save()
{
    QJsonObject jo;
    QFile saveFile(_path);

    QJsonObject UVTimeSpendObject;
    for(auto &i : UVTimeSpend.keys()){
        Json::setValue<int>(UVTimeSpendObject,i,UVTimeSpend[i]);
    }
    Hix::Common::Json::setValue<QJsonObject>(jo,"UV_time_spend",UVTimeSpendObject);

    QJsonObject motorTimeSpendObject;
    for(auto &i : motorTimeSpend.keys()){
        Json::setValue<int>(motorTimeSpendObject,i,motorTimeSpend[i]);
    }
    Hix::Common::Json::setValue<QJsonObject>(jo,"motor_time_spend",motorTimeSpendObject);

    Json::setValueArray<QString>(jo,"material_list",materialList);
    Json::setValueArray<QString>(jo,"enable_material_list",enableMaterialList);

    Json::setValue<int>(jo,"default_height",defaultHeight);
    Json::setValue<int>(jo,"height_offset",heightOffset);
    Json::setValue<int>(jo,"led_offset",ledOffset);

    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "save file open error";
    }
    _object = jo;
    QJsonDocument saveDoc(jo);

    saveFile.write(saveDoc.toJson());
}

QString PrinterSetting::serialize()
{

}
