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
        _opend = false;
        return;
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    _setting = loadDoc.object();

    _opend = true;
}
Version::~Version(){
//    delete _setting;
}
QString Version::getVersion()
{
    if(_opend)
        return _setting["version"].toString();
    else
        return "";
}
