#include "version.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>

constexpr auto _url = "/opt/capsuleFW/version.json";

Version::Version() : Hix::Common::Json::JsonSetting (_url)
{
    parse();
}

Version::~Version()
{

}

void Version::parse()
{
    try {
        version = Hix::Common::Json::getValue<QString>(_object,"version");
    } catch (std::runtime_error &e) {
        qDebug() << e.what();
    }
}

QString Version::serialize()
{
    QJsonDocument doc(_object);
    return doc.toJson();
}
