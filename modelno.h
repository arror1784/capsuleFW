#ifndef MODELNO_H
#define MODELNO_H

#include <QObject>

#include <QObject>
#include <QJsonObject>

class ModelNo : public QObject
{
    Q_OBJECT
private:
    ModelNo();
    ~ModelNo();

    static ModelNo* _ins;

    const QString _url = "/opt/capsuleFW/modelNo.json";

    QJsonObject _setting;

    bool _opend = false;

public:
    static ModelNo* GetInstance()
    {
        if (_ins == nullptr) {
            _ins = new ModelNo(/*filePath*/);
            atexit(release_instance);
        }
        return _ins;
    }
    static void release_instance() {
        if(_ins){
            delete _ins;
            _ins = nullptr;
        }
    }

    QString getModelNo();

};


#endif // MODELNO_H
