#include "printsetting.h"

#include <QFile>

PrintSetting* PrintSetting::_ins = nullptr;
const QString PrintSetting::filePath = QString("/opt/capsuleFW/setting.json");

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

    QFile saveFile(QStringLiteral("deviceInfo.json"));

    if(!saveFile.open(QIODevice::WriteOnly)){
//        qDebug() << "save file open error";
    }
    QJsonDocument saveDoc(setting);

    saveFile.write(saveDoc.toJson());
}

QString PrintSetting::getPrintSetting(QString key){
    return setting[key].toString();
}

void PrintSetting::setPrintSetting(QString key, QString value){
    setting[key] = value;
    saveFile();
}

QJsonObject PrintSetting::getResinSetting(QString type){
    return setting[type].toObject();
}

void PrintSetting::setResinSetting(QString type, QJsonObject value){
    setting[type] = value;
    saveFile();
}
