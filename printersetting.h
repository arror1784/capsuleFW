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
#include <QMap>

class PrinterSetting : public Hix::Common::Json::JsonSetting, public Hix::Common::Json::JsonReadSetting, public Hix::Common::Json::JsonWriteSetting
{
private:
    const QString _filePath = "/opt/capsuleFW/capsuleSetting.json";

public:
    PrinterSetting();

    void parse() override;
    void save() override;

    QMap<QString,int> UVTimeSpend;
    QMap<QString,int> motorTimeSpend;
    QVector<QString> materialList;
    QVector<QString> enableMaterialList;

    int defaultHeight;
    int heightOffset;
    double ledOffset;

};

#endif // PRINTSETTING_H
