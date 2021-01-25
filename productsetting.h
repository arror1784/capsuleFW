#ifndef PRODUCTSETTING_H
#define PRODUCTSETTING_H

#include "common/jsonreadsetting.h"
#include "common/jsonsetting.h"

enum class ProductType{
    C10,
    L10
};

class ProductSetting : public Hix::Common::Json::JsonSetting, public Hix::Common::Json::JsonReadSetting
{
public:
    ProductSetting();

    void parse() override;
    QString serialize() override;

    ProductType product;
};

#endif // PRODUCTSETTING_H
