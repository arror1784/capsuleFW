#include "printersetting.h"

#include <QFile>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

PrinterSetting* PrinterSetting::_ins = nullptr;
//const QString PrintSetting::filePath = QString("/opt/capsuleFW/capsuleSetting.json");

PrinterSetting::PrinterSetting()
{
    QFile loadFile(filePath);

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Could not open json file to read");
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    setting = loadDoc.object();
}


PrinterSetting::~PrinterSetting(){
//    delete setting;
}

void PrinterSetting::saveFile(){

    QFile saveFile(filePath);

    if(!saveFile.open(QIODevice::WriteOnly)){
        qDebug() << "save file open error";
    }
    QJsonDocument saveDoc(setting);

    saveFile.write(saveDoc.toJson());
}

QJsonValue PrinterSetting::getPrintSetting(QString key){
    return setting[key];
}

void PrinterSetting::setPrintSetting(QString key, double value){
    setting[key] = value;
    saveFile();
}
void PrinterSetting::setPrintSetting(QString key, int value){
    setting[key] = value;
    saveFile();
}
void PrinterSetting::setPrintSetting(QString key, QString value){
    setting[key] = value;
    saveFile();
}

void PrinterSetting::setPrintSetting(QString key, QJsonObject value)
{
    setting[key] = value;
    saveFile
            ();
}

QJsonArray PrinterSetting::getResinList(){
    if(setting["enable_material_list"].toArray().isEmpty()){
        return setting["material_list"].toArray();
    }else {
        return setting["enable_material_list"].toArray();
    }
}

void PrinterSetting::setResinList(QJsonArray value)
{
    setting["material_list"] = value;
    saveFile();
}

