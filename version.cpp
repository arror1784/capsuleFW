#include "version.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>

constexpr auto _url = "/opt/capsuleFW/version.json";

Version::Version() : Hix::Common::Json::JsonSetting (_url)
{

}

Version::~Version()
{

}

void Version::parse()
{
    version = Hix::Common::Json::getValue<QString>(_object,"version");
}

QString Version::serialize()
{
    QJsonDocument doc(_object);
    return doc.toJson();
}
