#ifndef ZIPCONTROL_H
#define ZIPCONTROL_H

#include <QObject>

class ZipControl : public QObject
{
    Q_OBJECT

public:
    explicit ZipControl(QObject *parent = nullptr);

    Q_INVOKABLE bool hasFile(QString path, QString target) const;
    Q_INVOKABLE QString getFileString(QString path, QString target) const;

signals:
    void pathChanged();

public slots:
};

#endif // ZIPCONTROL_H
