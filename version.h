#ifndef VERSION_H
#define VERSION_H

#include <QObject>
#include <QJsonObject>

#include "Singleton.h"

class Version : public QObject, public Hix::Common::Singleton<Version>
{
    Q_OBJECT
private:

    static Version* _ins;

    const QString _url = "/opt/capsuleFW/version.json";

    QJsonObject _setting;

    bool _opend = false;

public:    
    Version();
    ~Version();

    QString getVersion();

};

#endif // VERSION_H
