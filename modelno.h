#ifndef MODELNO_H
#define MODELNO_H

#include <QObject>

#include <QObject>
#include <QJsonObject>

#include "Singleton.h"

class ModelNo : public QObject, public Hix::Common::Singleton<ModelNo>
{
    Q_OBJECT
private:
    static ModelNo* _ins;

    const QString _url = "/opt/capsuleFW/modelNo.json";

    QJsonObject _setting;

    bool _opend = false;

public:
    ModelNo();
    ~ModelNo();

    QString getModelNo();

};


#endif // MODELNO_H
