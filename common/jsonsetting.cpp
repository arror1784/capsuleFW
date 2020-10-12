#include "jsonsetting.h"

#include <QFile>
#include <QJsonDocument>

Hix::Common::Json::JsonSetting::JsonSetting()
{

}

Hix::Common::Json::JsonSetting::JsonSetting(const QString& path) : _path(path)
{
    QFile loadFile(path);

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Could not open json file to read");
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    _object = loadDoc.object();
}
