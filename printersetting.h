#ifndef PRINTSETTING_H
#define PRINTSETTING_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "Singleton.h"

#include "common/jsonreadsetting.h"
#include "common/jsonsetting.h"
#include "common/jsonwritesetting.h"

#include "common/jsonutil.h"

#include <QJsonArray>
#include <vector>

class PrinterSetting : public Hix::Common::Singleton<PrinterSetting>, public Hix::Common::Json::JsonSetting, public Hix::Common::Json::JsonReadSetting, public Hix::Common::Json::JsonWriteSetting
{
private:
    const QString filePath = "/opt/capsuleFW/capsuleSetting.json";

public:
    PrinterSetting();

    void parse() override;
    void save() override;

    QVector<int> UVTimeSpend;
    QVector<int> motorTimeSpend;
    QVector<QString> materialList;
    QVector<QString> enableMaterialList;

    int defaultHeight;
    int heightOffset;
    double ledOffset;
    QString modelNo;


//    QJsonValue getPrintSetting(QString key);
//    void setPrintSetting(QString key,double value);
//    void setPrintSetting(QString key,int value);
//    void setPrintSetting(QString key,QString value);
//    void setPrintSetting(QString key,QJsonObject value);
//    QJsonArray getResinList();
//    void setResinList(QJsonArray value);
};

#endif // PRINTSETTING_H
