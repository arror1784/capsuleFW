#pragma once

#include <QJsonObject>

class QString;
namespace Hix {

    namespace Common {

        namespace Json {

            class JsonReadSetting
            {
            protected:
                virtual void parse() = 0;
                virtual QString serialize() = 0;
            };
        }
    }
}
