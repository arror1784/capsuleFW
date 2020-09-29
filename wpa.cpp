#include "wpa.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <QMap>
#include <QDebug>
#include <unistd.h>

#include <error.h>
#include <cstdlib>

#include <QVector>

using namespace std;

WPA::WPA() : _ctrlPath(WPA_CTRL_INTERFACE)
{
    ctrlConnect();
    runEvent();
}

WPA::WPA(const char *ctrl_path) : _ctrlPath(ctrl_path)
{
    ctrlConnect();
    runEvent();
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
    return wifiList.size();
}

WifiInfo *WPA::getNetwork(int index)
{
    return wifiList[index];
}

bool WPA::networkConnect(QString ssid, QString passwd)
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
    sprintf(buf,"ENABLE_NETWORK %d",id);
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

void WPA::ctrlConnect()
{
    _ctrl = wpa_ctrl_open(_ctrlPath.toStdString().data());
    _ctrl_event = wpa_ctrl_open(_ctrlPath.toStdString().data());

    refresh();
}

void WPA::wpa_ctrl_event()
{
    char *resBuff = new char[4096];
    size_t size = 4096;
    int a;

    if(wpa_ctrl_attach(_ctrl_event)){
        cout << "wpa attack error" << _ctrlPath.toStdString() << endl;
        return;
    }else{
        cout << "wpa attack sucess" << _ctrlPath.toStdString() << endl;
    }

    while (1) {
        memset(resBuff,'\0',size);
        size = 4096;

        wpa_ctrl_pending_blocking(_ctrl_event);
        wpa_ctrl_recv(_ctrl_event,resBuff,&size);
        cout << resBuff <<  endl;

        if(string(resBuff).find(WPA_EVENT_SCAN_RESULTS) != std::string::npos){
            clearList();
            parseWifiInfo();
            parseNetworkInfo();
            emit networkListUpdate();
        }else if(string(resBuff).find(WPA_EVENT_CONNECTED) != std::string::npos){
            refresh();
            emit currentStateChange();
        }else if(string(resBuff).find(WPA_EVENT_DISCONNECTED) != std::string::npos){
            refresh();
            emit currentStateChange();
        }
    }
}

void WPA::clearList()
{
    while(wifiList.size() > 0){
        delete wifiList[0];
        wifiList.removeAt(0);
    }
}

void WPA::refresh()
{
    char buff[4096] = {0};
    char resBuff[4096] = {0};

    wpa_ctrl_cmd(_ctrl,"STATUS",resBuff);

    string myStr(resBuff), val, line;
    stringstream ss(myStr);
    QStringList array;
    QMap<QString,QString> mp;


    while (getline(ss, line, '\n')) {
        vector<string> row;
        stringstream s(line);
        while (getline(s, val, '=')) {
            row.push_back (val);
        }
        mp.insert(QString::fromStdString(row[0]),QString::fromStdString(row[1]));
    }
    if(mp.contains("ssid")){
        _currentSSID = mp["ssid"];
    }else{
        _currentSSID = "";
    }

//    emit refreshAvailable();
}

QString WPA::currentSSID() const
{
    return _currentSSID;
}

int WPA::wpa_ctrl_cmd(struct wpa_ctrl *ctrl, char *cmd, char *buf)
{
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

    string myStr(resBuff), val, line;
    stringstream ss(myStr);

    while (getline(ss, line, '\n')) {
        QStringList row;
        stringstream s(line);
        if(first){
            first = false;
            continue;
        }
        while (getline(s, val, '\t')) {
            row.push_back(QString::fromStdString(val));
        }
        if(row.size() == 5){
            wifiList.push_back(new WifiInfo(-1,row[4],row[0],row[3],row[1].toInt(),row[2].toInt(),false));
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

    memset(resBuff,0x00,4096);
    ret = wpa_ctrl_cmd(_ctrl, "LIST_NETWORKS", resBuff);

    string myStr(resBuff), val, line;
    stringstream ss(myStr);

    while (getline(ss, line, '\n')) {
        QList<QString> row;
        stringstream s(line);
        if(first){
            first = false;
            continue;
        }
        while (getline(s, val, '\t')) {
            row.push_back(QString::fromStdString(val));
        }
        if(row.size() == 4){
            for (int i = 0; i < wifiList.size();i++) {
//                qDebug() << row[1] << row[2];
//                qDebug() << wifiList[i]->getSsid() << wifiList[i]->getBssid();
                if(wifiList[i]->getSsid() == row[1] && wifiList[i]->getBssid() == row[2]){
                    wifiList[i]->setSaved(true);
                    wifiList[i]->setNetworkID(row[0].toInt());
                }
            }
        }
    }
//    return vvs;
}
