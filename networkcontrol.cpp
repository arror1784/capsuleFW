#include "networkcontrol.h"

NetworkControl::NetworkControl(QObject *parent) : QObject(parent)
{

}


void NetworkControl::updateIpAddressList(){

    QList<QNetworkInterface> ipAddressesList = QNetworkInterface::allInterfaces();
    ipAddress.clear();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        ipAddress.insert(i,ipAddressesList.at(i).name() + " : " +  ipAddressesList.at(i).addressEntries().at(0).ip().toString());
    }
}
QList<QString> NetworkControl:: getIpAddressList(){
    return this->ipAddress;
}
