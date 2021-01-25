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
    if(Hix::Common::Json::tryGetValue(_object,"product",productStr)){
        if(productStr == "C10"){
            product = ProductType::C10;
        }else if(productStr == "L10"){
            product = ProductType::L10;
        }else{
            productStr = "C10";
            product = ProductType::C10;
        }
    }else{
        productStr = "C10";
        product = ProductType::C10;
    }
}

QString ProductSetting::serialize()
{
    QJsonDocument doc(_object);
    return doc.toJson();
}
