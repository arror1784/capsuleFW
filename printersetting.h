#ifndef PRINTSETTING_H
#define PRINTSETTING_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "Singleton.h"

class PrinterSetting : public QObject , public Hix::Common::Singleton<PrinterSetting>
{
    Q_OBJECT
private:
    static PrinterSetting* _ins;
    const QString filePath = "/opt/capsuleFW/capsuleSetting.json";
//    const QString resinPath = "/opt/capsuleFW/resin";

    QJsonObject setting;

public:
    PrinterSetting();
    ~PrinterSetting();

    void saveFile();

    QJsonValue getPrintSetting(QString key);
    void setPrintSetting(QString key,double value);
    void setPrintSetting(QString key,int value);
    void setPrintSetting(QString key,QString value);
    void setPrintSetting(QString key,QJsonObject value);
    QJsonArray getResinList();
    void setResinList(QJsonArray value);
};

#endif // PRINTSETTING_H
