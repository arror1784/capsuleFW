#include "networkcontrol.h"

NetworkControl::NetworkControl(QObject *parent) : QObject(parent)
{

}


void NetworkControl::updateIpAddressList(){

//    QList<QNetworkInterface> ipAddressesList = QNetworkInterface::allInterfaces();
//    ipAddress.clear();
////        ipAddress.insert(i,ipAddressesList.at(i).name() + " : " +  ipAddressesList.at(i).addressEntries().at(0).ip().toString());
//    }
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    ipAddress.clear();

    for (int i = 0; i < ipAddressesList.length(); i++) {
        if (ipAddressesList[i].protocol() == QAbstractSocket::IPv4Protocol && ipAddressesList[i] != localhost)
            ipAddress.insert(i,ipAddressesList[i].toString());
    }
}

QList<QString> NetworkControl:: getIpAddressList(){
    return this->ipAddress;
}
