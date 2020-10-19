#include "modelno.h"

#include <QJsonDocument>
#include <QDebug>


constexpr auto _url = "/opt/capsuleFW/modelNo.json";

ModelNo::ModelNo() : Hix::Common::Json::JsonSetting (_url)
{
}
ModelNo::~ModelNo(){
}

void ModelNo::parse()
{
    modelNo = Hix::Common::Json::getValue<QString>(_object,"modelNo");
}

QString ModelNo::serialize()
{
    QJsonDocument doc(_object);
    return doc.toJson();
}
