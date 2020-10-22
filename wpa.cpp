#include "wpa.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <QMap>
#include <QDebug>
#include <QThread>
#ifndef _MSC_VER
#include "wpa_ctrl/wpa_ctrl.h"
#include <unistd.h>

#include <error.h>

#endif
#include <cstdlib>

#include <QVector>

WPA::WPA() : _ctrlPath(WPA_CTRL_INTERFACE)
{
    ctrlConnect();
    runEvent();
    checkConnected();
}

WPA::WPA(const char *ctrl_path) : _ctrlPath(ctrl_path)
{
    ctrlConnect();
    runEvent();
    checkConnected();
}

void WPA::runEvent()
{
    th = std::thread(&WPA::wpa_ctrl_event,this);
}

void WPA::networkScan()
{
    int ret;
    char resBuff[4096] = {0};

    ret = wpa_ctrl_cmd(_ctrl, "SCAN", resBuff);

}

int WPA::networkCount()
{
    return _wifiList.size();
}

WifiInfo *WPA::getNetwork(int index)
{
    return _wifiList[index];
}

bool WPA::networkConnect(QString ssid,QString bssid, QString passwd,int networkID)
{
    char buf[4096] = {0};
    char resBuff[4096] = {0};
    int id = -1;

    if(networkID == -1){
        networkConnect(ssid,bssid,passwd);
    }

    id = networkID;

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d ssid \"%s\"",id,ssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d bssid %s",id,bssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d psk \"%s\"",id,passwd.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SELECT_NETWORK %d",id);
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    wpa_ctrl_cmd(_ctrl,"SAVE_CONFIG",resBuff);

    return true;
}

bool WPA::networkConnect(QString ssid,QString bssid, QString passwd)
{
    char buf[4096] = {0};
    char resBuff[4096] = {0};
    int id = -1;

    memset(resBuff,0x00,4096);
    sprintf(buf,"ADD_NETWORK");
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    id = atoi(resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d ssid \"%s\"",id,ssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d bssid %s",id,bssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d psk \"%s\"",id,passwd.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SELECT_NETWORK %d",id);
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    wpa_ctrl_cmd(_ctrl,"SAVE_CONFIG",resBuff);

    return true;
}

bool WPA::networkConnect(int id)
{
    char buf[4096] = {0};
    char resBuff[4096] = {0};

    memset(resBuff,0x00,4096);
    sprintf(buf,"SELECT_NETWORK %d",id);
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    wpa_ctrl_cmd(_ctrl,"SAVE_CONFIG",resBuff);

    return true;
}

bool WPA::networkConnect(QString ssid,QString bssid, int networkID)
{
    char buf[4096] = {0};
    char resBuff[4096] = {0};
    int id = -1;

    if(networkID == -1){
        networkConnect(ssid,bssid);
    }

    id = networkID;

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d ssid \"%s\"",id,ssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d bssid %s",id,bssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d key_mgmt NONE",id);
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SELECT_NETWORK %d",id);
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    wpa_ctrl_cmd(_ctrl,"SAVE_CONFIG",resBuff);

    return true;
}

bool WPA::networkConnect(QString ssid,QString bssid)
{
    char buf[4096] = {0};
    char resBuff[4096] = {0};
    int id = -1;

    memset(resBuff,0x00,4096);
    sprintf(buf,"ADD_NETWORK");
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    id = atoi(resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d ssid \"%s\"",id,ssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d bssid %s",id,bssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SET_NETWORK %d key_mgmt NONE",id);
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    sprintf(buf,"SELECT_NETWORK %d",id);
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    memset(resBuff,0x00,4096);
    wpa_ctrl_cmd(_ctrl,"SAVE_CONFIG",resBuff);

    return true;
}

bool WPA::networkDisconnect()
{
    char resBuff[4096] = {0};

    wpa_ctrl_cmd(_ctrl,"DISCONNECT",resBuff);

    return true;
}

void WPA::networkDelete(QString ssid)
{

}

void WPA::networkDelete(int id)
{
    char buf[4096] = {0};
    char resBuff[4096] = {0};

    memset(resBuff,0x00,4096);
    sprintf(buf,"REMOVE_NETWORK %d",id);
    wpa_ctrl_cmd(_ctrl,buf,resBuff);
}

void WPA::checkNetworkConnect()
{
    qDebug() << "WPA" << QThread::currentThread();
    checkConnected();
}

void WPA::ctrlConnect()
{
#ifndef _MSC_VER

    _ctrl = wpa_ctrl_open(_ctrlPath.toStdString().data());
    _ctrl_event = wpa_ctrl_open(_ctrlPath.toStdString().data());

//    checkConnected();
#endif
}

void WPA::wpa_ctrl_event()
{
#ifndef _MSC_VER
    char *resBuff = new char[4096];
    size_t size = 4096;
    int a;

    if(wpa_ctrl_attach(_ctrl_event)){
        std::cout << "wpa attack error" << _ctrlPath.toStdString() << endl;
        return;
    }else{
        std::cout << "wpa attack sucess" << _ctrlPath.toStdString() << endl;
    }

    while (1) {
        memset(resBuff,'\0',size);
        size = 4096;

        wpa_ctrl_pending_blocking(_ctrl_event);
        wpa_ctrl_recv(_ctrl_event,resBuff,&size);
//        cout << resBuff <<  endl;

        if(std::string(resBuff).find(WPA_EVENT_SCAN_RESULTS) != std::string::npos){
            clearList();
            parseWifiInfo();
            parseNetworkInfo();
//            checkConnected();
            emit networkListUpdate();
        }else if(std::string(resBuff).find(WPA_EVENT_CONNECTED) != std::string::npos){
            _connected = true;
            checkConnected();
            emit currentStateChange();

        }else if(std::string(resBuff).find(WPA_EVENT_DISCONNECTED) != std::string::npos){
            _connected = false;
            checkConnected();
            _currentSSID = "";
            _connected = false;
            for (int i = 0; i < _wifiList.size();i++) {
                _wifiList[i]->setConnected(false);
            }
            emit connectedChange(false);
            emit currentStateChange();

        }else if(std::string(resBuff).find(WPA_EVENT_SCAN_FAILED) != std::string::npos){
            checkConnected();
            emit currentStateChange();
        }
    }
#endif
}

void WPA::clearList()
{
    while(_wifiList.size() > 0){
        delete _wifiList[0];
        _wifiList.removeAt(0);
    }
}

QString WPA::currentSSID() const
{
    return _currentSSID;
}

int WPA::wpa_ctrl_cmd(struct wpa_ctrl *ctrl, char *cmd, char *buf)
{
#ifndef _MSC_VER

    int ret;
    size_t len = 4096;

    ret = wpa_ctrl_request(ctrl, cmd, strlen(cmd), buf, &len, NULL);
    if (ret == -2) {
        printf("'%s' command timed out.\n", cmd);
        return -2;
    } else if (ret < 0) {
        printf("'%s' command failed.\n", cmd);
        return -1;
    }
    buf[len -1] = '\0';
#endif
    return 0;

}

void WPA::parseWifiInfo()
{
    int r_size = 0;
    bool first = true;

    int ret;
    char resBuff[4096] = {0};

    memset(resBuff,0x00,4096);
    ret = wpa_ctrl_cmd(_ctrl, "SCAN_RESULTS", resBuff);

    std::string myStr(resBuff), val, line;
    std::stringstream ss(myStr);

    while (getline(ss, line, '\n')) {
        QStringList row;
        std::stringstream s(line);
        if(first){
            first = false;
            continue;
        }
        while (getline(s, val, '\t')) {
            row.push_back(QString::fromStdString(val));
        }
        if(row.size() == 5){
            if(row[3].contains("WPA")){
                _wifiList.push_back(new WifiInfo(-1,row[4],row[0],true,row[1].toInt(),row[2].toInt(),false,false));
            }else{
                _wifiList.push_back(new WifiInfo(-1,row[4],row[0],false,row[1].toInt(),row[2].toInt(),false,false));
            }
        }
    }

    return;
}

void WPA::parseNetworkInfo()
{
    int r_size = 0;
    bool first = true;

    int ret;
    char resBuff[4096] = {0};

    do {

        memset(resBuff,0x00,4096);
        ret = wpa_ctrl_cmd(_ctrl, "LIST_NETWORKS", resBuff);

    } while (std::string(resBuff) == "OK");

    std::string myStr(resBuff), val, line;
    std::stringstream ss(myStr);

    while (getline(ss, line, '\n')) {
        QList<QString> row;
        std::stringstream s(line);
        if(first){
            first = false;
            continue;
        }
        while (getline(s, val, '\t')) {
            row.push_back(QString::fromStdString(val));
        }
//        if(row.size() == 4){
        for (int i = 0; i < _wifiList.size();i++) {
            if(_wifiList[i]->getSsid() == row[1] && _wifiList[i]->getBssid() == row[2]){
                _wifiList[i]->setSaved(true);
                _wifiList[i]->setNetworkID(row[0].toInt());
            }
        }
//        }
    }
//    return vvs;
}

void WPA::checkConnected()
{
    char buff[4096] = {0};
    char resBuff[4096] = {0};

    wpa_ctrl_cmd(_ctrl,"STATUS",resBuff);

    std::string myStr(resBuff), val, line;
    std::stringstream ss(myStr);
    QStringList array;
    QMap<QString,QString> mp;

    while (getline(ss, line, '\n')) {
        std::vector<std::string> row;
        std::stringstream s(line);
        while (getline(s, val, '=')) {
            row.push_back (val);
        }
        mp.insert(QString::fromStdString(row[0]),QString::fromStdString(row[1]));
    }
    if(mp["wpa_state"] == "COMPLETED"){
        _currentSSID = mp["ssid"];

        for (int i = 0; i < _wifiList.size();i++) {
            if(_wifiList[i]->getSsid() == mp["ssid"] && _wifiList[i]->getBssid() == mp["bssid"]){
                _wifiList[i]->setConnected(true);
            }
        }
        _connected = true;
        emit connectedChange(true);
    }else{
        _currentSSID = "";
        _connected = false;
        emit connectedChange(false);
    }
    return;
}
