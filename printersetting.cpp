#include "printersetting.h"

#include <QFile>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

using namespace Hix::Common;
PrinterSetting::PrinterSetting() : Hix::Common::Json::JsonSetting (_filePath)
{

}

void PrinterSetting::parse()
{
    UVTimeSpend = Json::getValueArray<int>(_object,"UV_time_spend");
    motorTimeSpend = Json::getValueArray<int>(_object,"motor_time_spend");
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

    Json::setValueArray<int>(jo,"UV_time_spend",UVTimeSpend);
    Json::setValueArray<int>(jo,"motor_time_spend",motorTimeSpend);
    Json::setValueArray<QString>(jo,"material_list",materialList);
    Json::setValueArray<QString>(jo,"enable_material_list",enableMaterialList);

    Json::setValue<int>(jo,"default_height",defaultHeight);
    Json::setValue<int>(jo,"height_offset",heightOffset);
    Json::setValue<int>(jo,"led_offset",ledOffset);

    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "save file open error";
    }
    QJsonDocument saveDoc(jo);

    saveFile.write(saveDoc.toJson());
}
