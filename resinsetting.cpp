#include "resinsetting.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

ResinSetting::ResinSetting(QString path):
    filePath(resinPath + "/" + path + ".json")
{
    QFile loadFile(filePath);
    if(!loadFile.open(QIODevice::ReadWrite | QIODevice::ExistingOnly)){
        qDebug() << "Could not open json file to ReadWrite " << filePath;
        qDebug() << loadFile.errorString();
        _open = false;
    }else{
        _open = true;
    }
    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
//    QJsonArray ja = loadDoc.array();

    setting = loadDoc.object();
}
void ResinSetting::saveFile(){

    if(!_open)
        return;
    QFile saveFile(filePath);

    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "save file open error";
    }
    QJsonDocument saveDoc(setting);

    saveFile.write(saveDoc.toJson());
}

QJsonValue ResinSetting::getResinSetting(QString key){
    if(!_open)
        return setting[key];
    return setting[key];
}
void ResinSetting::setResinSetting(QString key, double value){
    if(!_open)
        return;
    setting[key] = value;
    saveFile();
}
void ResinSetting::setResinSetting(QString key, int value){
    if(!_open)
        return;
    setting[key] = value;
    saveFile();
}
void ResinSetting::setResinSetting(QString key, QString value){
    if(!_open)
        return;
    setting[key] = value;
    saveFile();
}

void ResinSetting::setResinSetting(QJsonObject value)
{
    if(!_open)
        return;
    setting = value;
    saveFile();
}

bool ResinSetting::getOpen() const
{
    return _open;
}
