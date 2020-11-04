#pragma once

#include <QJsonObject>
#include <QString>
#include <QVariant>
#include <QJsonArray>
#include <QVector>
#include <QVariantList>
#include <stdexcept>

namespace Hix {
    namespace Common {
        namespace Json {
            template<typename ValueType>
            ValueType getValue(const QJsonObject& json,const QString& key)
            {
                if(json.contains(key))
                    return json[key].toVariant().value<ValueType>();
                else
                    throw std::runtime_error("value doesnt exist for given key");
            }
            template<typename ValueType>
            QVector<ValueType> getValueArray(const QJsonObject& json,const QString& key)
            {
                QVector<ValueType> vc;
                if(json.contains(key))
                {
                    for(auto i : json[key].toArray().toVariantList())
                    {
                        vc.push_back(i.value<ValueType>());
                    }

                    return vc;
                }
                else
                    throw std::runtime_error("value doesnt exist for given key");
            }

            template<typename ValueType>
            void setValue(QJsonObject& json,const QString& key,const ValueType& value)
            {
                json[key] = value;
            }
            template<typename ValueType>
            void setValueArray(QJsonObject& json,const QString& key,const QVector<ValueType>& value)
            {
                QList<QVariant> lv;
                for(auto& i : value){
                    lv.push_back(i);
                }
                json[key] = QJsonArray::fromVariantList(lv);
            }
        }
    }
}
