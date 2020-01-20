#ifndef PRINTSETTING_H
#define PRINTSETTING_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class PrintSetting : public QObject
{
    Q_OBJECT
private:
    PrintSetting();
    PrintSetting(QString settingPath);
    PrintSetting(const PrintSetting& other);
//    ~PrintSetting();

    static PrintSetting* _ins;

public:
    static PrintSetting* GetInstance()
    {
        if (_ins == nullptr) {
            _ins = new PrintSetting("log.txt");
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
    void getPrintSetting();
    void setPrintSetting();
    QJsonObject getPrintSetting(int reginType);
};

#endif // PRINTSETTING_H
