#include "modelno.h"

#include <QJsonDocument>
#include <QDebug>


constexpr auto _url = "/opt/capsuleFW/modelNo.json";

ModelNo::ModelNo() : Hix::Common::Json::JsonSetting (_url)
{
    parse();
}
ModelNo::~ModelNo(){
}

void ModelNo::parse()
{
    try {
        modelNo = Hix::Common::Json::getValue<QString>(_object,"modelNo");
    } catch (std::runtime_error &e) {
        qDebug() << e.what();
    }
}

QString ModelNo::serialize()
{
    QJsonDocument doc(_object);
    return doc.toJson();
}
