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
    int id;

    if(networkID == -1){
        id = networkAdd();
    }else{
        id = networkID;
    }

    networkSet(id,"ssid",ssid.toStdString());
    networkSet(id,"bssid",bssid.toStdString());

    if(passwd.isEmpty()){
        networkSet(id,"key_mgmt","NONE");
    }else{
        networkSet(id,"psk",passwd.toStdString());
    }

    networkSelect(id);

    return true;
}

bool WPA::networkConnect(int id)
{
    networkSelect(id);
    return true;
}

bool WPA::networkDisconnect()
{
    char resBuff[4096] = {0};

    wpa_ctrl_cmd(_ctrl,"DISCONNECT",resBuff);

    return true;
}
void WPA::networkDelete(int id)
{
    char resBuff[4096] = {0};

    std::string buf;
    buf = "REMOVE_NETWORK ";
    buf += std::to_string(id);

    wpa_ctrl_cmd(_ctrl,buf.c_str(),resBuff);
}

void WPA::checkNetworkConnect()
{
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
        qDebug() << resBuff;
        std::string stdResBuff = resBuff;
        if(stdResBuff.find(WPA_EVENT_SCAN_RESULTS) != std::string::npos){
            clearList();
            parseWifiInfo();
            parseNetworkInfo();
            checkConnected();
            emit networkListUpdate();
        }else if(stdResBuff.find(WPA_EVENT_CONNECTED) != std::string::npos){
            _connected = true;
            checkConnected();
            networkSaveConfig();            
            emit currentStateChange();
            emit connectedChange(true);

        }else if(stdResBuff.find(WPA_EVENT_DISCONNECTED) != std::string::npos){
            _connected = false;
            checkConnected();
            _currentSSID = "";
            _connected = false;
            for (int i = 0; i < _wifiList.size();i++) {
                _wifiList[i]->setConnected(false);
            }
            emit currentStateChange();
            emit connectedChange(false);

        }else if(stdResBuff.find(WPA_EVENT_SCAN_FAILED) != std::string::npos){
            qDebug() << "weggwegweg";
            auto pos = stdResBuff.find("ret=");
            if(pos != std::string::npos){
                auto ret = stdResBuff.substr(pos+4);
                qDebug() << atoi(ret.c_str());

                if(atoi(ret.c_str()) == -52){
                    
                    emit wifiConnectError();
                }
            }
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

int WPA::wpa_ctrl_cmd(struct wpa_ctrl *ctrl, const char *cmd, char *buf)
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
//        emit connectedChange(true);
    }else{
        _currentSSID = "";
        _connected = false;
//        emit connectedChange(false);
    }
    return;
}

int WPA::networkAdd()
{
    char resBuff[4096] = {0};

    wpa_ctrl_cmd(_ctrl,"ADD_NETWORK",resBuff);

    return atoi(resBuff);
}

void WPA::networkSelect(int id)
{
    char resBuff[4096] = {0};

    std::string buf;
    buf = "SELECT_NETWORK ";
    buf += std::to_string(id);

    wpa_ctrl_cmd(_ctrl,buf.c_str(),resBuff);
}

void WPA::networkSaveConfig()
{
    char resBuff[4096] = {0};

    wpa_ctrl_cmd(_ctrl,"SAVE_CONFIG",resBuff);
}

void WPA::networkSet(int id, std::string key, std::string value)
{
    char resBuff[4096] = {0};

    std::string buf;
    buf = "SET_NETWORK ";
    buf += std::to_string(id);
    buf += " ";
    buf += key;
    buf += " ";
    if(key == "ssid" || key == "psk"){
        std::string stdValue = value;
        stdValue.push_back('"');
        stdValue.insert(0,1,'"');
        buf += stdValue;
    }else
        buf += value;

    wpa_ctrl_cmd(_ctrl,buf.c_str(),resBuff);
}
