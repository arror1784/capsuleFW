#ifndef INFOSETTING_H
#define INFOSETTING_H

#include "common/jsonreadsetting.h"
#include "common/jsonsetting.h"

#include "common/jsonutil.h"

class InfoSetting : public Hix::Common::Json::JsonSetting, public Hix::Common::Json::JsonReadSetting
{
public:
    InfoSetting(QString& path);
    ~InfoSetting();

    void parse() override;
    QString serialize() override;

    double layerHeight;
    int totalLayer;
};

#endif // INFOSETTING_H
