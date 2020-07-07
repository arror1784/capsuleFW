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
    if(!loadFile.open(QIODevice::ReadWrite)){
        qDebug() << "Could not open json file to ReadWrite " << filePath;
        qDebug() << loadFile.errorString();
    }
    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
//    QJsonArray ja = loadDoc.array();

    setting = loadDoc.object();
}
void ResinSetting::saveFile(){

    QFile saveFile(filePath);

    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "save file open error";
    }
    QJsonDocument saveDoc(setting);

    saveFile.write(saveDoc.toJson());
}

QJsonValue ResinSetting::getResinSetting(QString key){
    return setting[key];
}
void ResinSetting::setResinSetting(QString key, double value){
    setting[key] = value;
    saveFile();
}
void ResinSetting::setResinSetting(QString key, int value){
    setting[key] = value;
    saveFile();
}
void ResinSetting::setResinSetting(QString key, QString value){
    setting[key] = value;
    saveFile();
}

void ResinSetting::setResinSetting(QJsonObject value)
{
    setting = value;
    saveFile();
}
