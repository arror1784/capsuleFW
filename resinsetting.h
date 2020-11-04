#ifndef RESINSETTING_H
#define RESINSETTING_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include <unordered_map>


#include "common/jsonreadsetting.h"
#include "common/jsonsetting.h"
#include "common/jsonwritesetting.h"

#include "common/jsonutil.h"


class ResinSetting : public Hix::Common::Json::JsonSetting, public Hix::Common::Json::JsonReadSetting, public Hix::Common::Json::JsonWriteSetting
{
private:

public:
    ResinSetting(QString resin/*,QString layerHeight*/);
    ~ResinSetting() override;

    struct resinInfo{
        double resinLedOffset;
        double contractionRatio;
        double layerHeight;
        int bedCuringLayer;
        int curingTime;
        int zHopHeight;
        int maxSpeed;
        int initSpeed;
        int upAccelSpeed;
        int upDecelSpeed;
        int downAccelSpeed;
        int downDecelSpeed;
        int bedCuringTime;
        int layerDelay;
        int material;
    };

    QString lastUpdate;
    QMap<QString,resinInfo> resinList;

    void parse() override;
    QString serialize() override;
    void save() override;

    bool removeFile();
    bool createFile();

};

#endif // RESINSETTING_H
