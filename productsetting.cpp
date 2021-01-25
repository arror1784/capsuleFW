#include "productsetting.h"

#include <QJsonDocument>
#include "common/jsonutil.h"

constexpr auto _url = "/opt/capsuleFW/product.json";

ProductSetting::ProductSetting() : Hix::Common::Json::JsonSetting (_url)
{
    parse();
}

void ProductSetting::parse()
{
    QString productTypeString;
    if(Hix::Common::Json::tryGetValue(_object,"product",productTypeString)){
        if(productTypeString == "C10"){
            product = ProductType::C10;
        }else if(productTypeString == "L10"){
            product = ProductType::L10;
        }else{
            product = ProductType::C10;
        }
    }else{
        product = ProductType::C10;
    }
}

QString ProductSetting::serialize()
{
    QJsonDocument doc(_object);
    return doc.toJson();
}
