#ifndef ZIPCONTROL_H
#define ZIPCONTROL_H

#include <QObject>

class ZipControl : public QObject
{
    Q_OBJECT
public:
    explicit ZipControl(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ZIPCONTROL_H
