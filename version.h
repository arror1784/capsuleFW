#ifndef VERSION_H
#define VERSION_H

#include <QObject>
#include <QJsonObject>

class Version : public QObject
{
    Q_OBJECT
private:
    Version();
    ~Version();

    static Version* _ins;

    const QString _url = "/opt/capsuleFW/version.json";

    QJsonObject _setting;

public:
    static Version* GetInstance()
    {
        if (_ins == nullptr) {
            _ins = new Version(/*filePath*/);
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

    QString getVersion();

};

#endif // VERSION_H
