#ifndef RESINSETTING_H
#define RESINSETTING_H

#include <QObject>
#include <QJsonObject>

class ResinSetting
{
public:
    ResinSetting(QString path);

    QJsonObject getJsonObject(){return setting;}

    void saveFile();

    QJsonValue getResinSetting(QString key);
    void setResinSetting(QString key,double value);
    void setResinSetting(QString key,int value);
    void setResinSetting(QString key,QString value);

    void setResinSetting(QJsonObject value);

private:
    const QString resinPath = "/opt/capsuleFW/resin";
    QJsonObject setting;
    QString filePath;

};

#endif // RESINSETTING_H
