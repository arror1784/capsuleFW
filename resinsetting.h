#ifndef RESINSETTING_H
#define RESINSETTING_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>

class ResinSetting
{
public:
    ResinSetting(QString path/*,QString layerHeight*/);

    QJsonObject getJsonObject(){return setting;}
    QJsonObject getJsonObjectLayerHeight(double layerHeight){
        QString s;
        s.setNum(layerHeight);
        qDebug() << s << "hello my friend";
        return setting[s].toObject();
    }


    void saveFile();

    bool removeFile();

    QJsonValue getResinSetting(QString key);
    void setResinSetting(QString key,double value);
    void setResinSetting(QString key,int value);
    void setResinSetting(QString key,QString value);

    void setResinSetting(QJsonObject value);

    bool getOpen() const;

private:
    const QString resinPath = "/opt/capsuleFW/resin";
    QJsonObject setting;
    QString filePath;

    bool _open = false;
    QString _layerHeight;

};

#endif // RESINSETTING_H
