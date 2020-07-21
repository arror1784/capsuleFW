#include "printsetting.h"

#include <QFile>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

PrintSetting* PrintSetting::_ins = nullptr;
//const QString PrintSetting::filePath = QString("/opt/capsuleFW/capsuleSetting.json");

PrintSetting::PrintSetting()
{
    QFile loadFile(filePath);

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Could not open json file to read");
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    setting = loadDoc.object();
}

PrintSetting::PrintSetting(QString settingPath)
{
    QFile loadFile(settingPath);

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Could not open json file to read");
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    setting = loadDoc.object();
}

PrintSetting::~PrintSetting(){
//    delete setting;
}

void PrintSetting::saveFile(){

    QFile saveFile(filePath);

    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "save file open error";
    }
    QJsonDocument saveDoc(setting);

    saveFile.write(saveDoc.toJson());
}

QJsonValue PrintSetting::getPrintSetting(QString key){
    return setting[key];
}
void PrintSetting::setPrintSetting(QString key, double value){
    setting[key] = value;
    saveFile();
}
void PrintSetting::setPrintSetting(QString key, int value){
    setting[key] = value;
    saveFile();
}
void PrintSetting::setPrintSetting(QString key, QString value){
    setting[key] = value;
    saveFile();
}

void PrintSetting::setPrintSetting(QString key, QJsonObject value)
{
    setting[key] = value;
    saveFile();
}

QJsonArray PrintSetting::getResinList(){
    if(setting["enable_material_list"].toArray().isEmpty()){
        return setting["material_list"].toArray();
    }else {
        return setting["enable_material_list"].toArray();
    }
}

void PrintSetting::setResinList(QJsonArray value)
{
    setting["material_list"] = value;
    saveFile();
}

