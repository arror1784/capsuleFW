#include "modelno.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>

ModelNo* ModelNo::_ins = nullptr;

ModelNo::ModelNo()
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
ModelNo::~ModelNo(){
//    delete _setting;
}
QString ModelNo::getModelNo()
{
    if(_opend)
        return _setting["modelNo"].toString();
    else
        return "";
}
