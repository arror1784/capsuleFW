#pragma once

#include <QJsonObject>

class QString;
namespace Hix {

    namespace Common {

        namespace Json {

            class JsonSetting
            {
            public:
                JsonSetting(QString& path);
            protected:
                QJsonObject _object;
                QString _path;
            };
        }
    }
}
