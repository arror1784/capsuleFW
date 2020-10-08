#pragma once

#include <QJsonObject>

class QString;
namespace Hix {

    namespace Common {

        namespace Json {

            class JsonReadSetting
            {
            public:
                JsonReadSetting();
            protected:
                virtual void parse() = 0;
            };
        }
    }
}
