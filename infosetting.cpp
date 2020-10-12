#include "infosetting.h"

//InfoSetting::InfoSetting(QString& path)
//{

//}

InfoSetting::InfoSetting(QString &path) : Hix::Common::Json::JsonSetting (path)
{

}

void InfoSetting::parse()
{
    layerHeight = Hix::Common::Json::getValue<double>(_object,"layer_height");
    totalLayer = Hix::Common::Json::getValue<int>(_object,"total_layer");
}
