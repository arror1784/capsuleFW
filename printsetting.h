#ifndef PRINTSETTING_H
#define PRINTSETTING_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class PrintSetting : public QObject
{
    Q_OBJECT
private:
    PrintSetting();
    PrintSetting(QString settingPath);
    PrintSetting(const PrintSetting& other);
    ~PrintSetting();

    static PrintSetting* _ins;
    QString filePath = "/opt/capsuleFW/capsuleSetting.json";

    QJsonObject setting;

public:
    static PrintSetting* GetInstance()
    {
        if (_ins == nullptr) {
            _ins = new PrintSetting(/*filePath*/);
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

    void saveFile();

    QJsonValue getPrintSetting(QString key);
    void setPrintSetting(QString key,double value);
    void setPrintSetting(QString key,int value);
    void setPrintSetting(QString key,QString value);

    QJsonObject getResinSetting(QString type);
    void setResinSetting(QString type, QJsonObject value);
//    QJsonObject getPrintSetting(int reginType);

    QJsonArray getResinList();

};

#endif // PRINTSETTING_H
