#ifndef VERSION_H
#define VERSION_H

#include "Singleton.h"

#include "common/jsonreadsetting.h"
#include "common/jsonsetting.h"

#include "common/jsonutil.h"

class Version : public Hix::Common::Singleton<Version>, public Hix::Common::Json::JsonSetting, public Hix::Common::Json::JsonReadSetting
{
public:    
    Version();
    ~Version();

    void parse() override;
    QString serialize() override;

    QString version;

};

#endif // VERSION_H
