#pragma once

#include <QJsonObject>

class QString;
namespace Hix {

    namespace Common {

        namespace Json {

            class JsonWriteSetting
            {
            protected:
                virtual void save() = 0;
            };
        }
    }
}
