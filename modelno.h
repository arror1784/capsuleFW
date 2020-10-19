#ifndef MODELNO_H
#define MODELNO_H

#include "Singleton.h"

#include "common/jsonreadsetting.h"
#include "common/jsonsetting.h"

#include "common/jsonutil.h"

class ModelNo : public QObject, public Hix::Common::Singleton<ModelNo>, public Hix::Common::Json::JsonSetting, public Hix::Common::Json::JsonReadSetting
{
public:
    ModelNo();
    ~ModelNo();

    void parse() override;
    QString serialize() override;

    QString modelNo;

};

#endif // MODELNO_H
