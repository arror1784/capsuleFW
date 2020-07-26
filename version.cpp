#include "version.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>

Version* Version::_ins = nullptr;

Version::Version()
{
    QFile loadFile(_url);

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Could not open json file to read");
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    _setting = loadDoc.object();
}
Version::~Version(){
//    delete _setting;
}
QString Version::getVersion()
{
    return _setting["version"].toString();
}
