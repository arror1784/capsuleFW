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
                    std::runtime_error("value doesnt exist for given key");
            }
            template<typename ValueType>
            std::vector<ValueType> getValueArray(const QJsonObject& json,const QString& key)
            {
                std::vector<ValueType> vc;
                if(json.contains(key))
                {
                    for(auto i : json[key].toArray().toVariantList())
                    {
                        vc.insert(i.value<ValueType>());
                    }

                    return vc;
                }
                else
                    std::runtime_error("value doesnt exist for given key");
            }

            template<typename ValueType>
            void setValue(QJsonObject& json,const QString& key,const ValueType& value)
            {
                json[key] = value;
            }
            template<typename ValueType>
            void setValueArray(QJsonObject& json,const QString& key,const std::vector<ValueType>& value)
            {
                QVector<ValueType> vc = QVector<ValueType>::fromStdVector(value);

                json[key] = QJsonArray::fromStringList(VariantList(vc.toList()));
            }
        }
    }
}
