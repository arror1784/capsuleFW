#ifndef NETWORKCONTROL_H
#define NETWORKCONTROL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QNetworkInterface>

class NetworkControl : public QObject
{
    Q_OBJECT
public:
    explicit NetworkControl(QObject *parent = nullptr);

signals:

public slots:
    void updateIpAddressList();
    QList<QString> getIpAddressList();

private:
    QList<QString> ipAddress;
};

#endif // NETWORKCONTROL_H
