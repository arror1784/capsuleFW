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

QStringList WPA::networkList()
{
    int ret;
    char resBuff[4096] = {0};

    ret = wpa_ctrl_cmd(_ctrl, "SCAN_RESULTS", resBuff);

    return parse_to_wifi_name(resBuff);
}

bool WPA::networkConnect(QString ssid, QString passwd)
{
    char buf[4096] = {0};
    char resBuff[4096] = {0};

    qDebug() << "networkConnect" << ssid << passwd;

    sprintf(buf,"SET_NETWORK 0 ssid \"%s\"",ssid.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    sprintf(buf,"SET_NETWORK 0 psk \"%s\"",passwd.toStdString().data());
    wpa_ctrl_cmd(_ctrl,buf,resBuff);

    wpa_ctrl_cmd(_ctrl,"ENABLE_NETWORK 0",resBuff);

    wpa_ctrl_cmd(_ctrl,"SAVE_CONFIG",resBuff);

    return true;
}

bool WPA::networkDisconnect()
{
    char resBuff[4096] = {0};

    wpa_ctrl_cmd(_ctrl,"DISCONNECT",resBuff);

    return true;
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
            cout << "asdasd" << endl;
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

QStringList WPA::parse_to_wifi_name(char *buff)
{
    int r_size = 0;
    bool first = true;
    string myStr(buff), val, line;
    stringstream ss(myStr);
    QStringList array;

    while (getline(ss, line, '\n')) {
        vector<string> row;
        stringstream s(line);
        if(first){
            first = false;
            continue;
        }
        while (getline(s, val, '\t')) {
            row.push_back (val);
        }
        if(!array.contains(QString(row.at(4).c_str()))){
            array.push_back(QString(row.at(4).c_str()));
            r_size++;
        }
    }

    for (int i = 1; i < r_size -1;i++) {
        cout << '\t' << array[i].toStdString() << endl;
    }

    return array;
}

QStringList WPA::parse_to_network_list(char *buff)
{
    int r_size = 0;
    bool first = true;
    string myStr(buff), val, line;
    stringstream ss(myStr);
    QStringList array;

    while (getline(ss, line, '\n')) {
        vector<string> row;
        stringstream s(line);
        if(first){
            first = false;
            continue;
        }
        while (getline(s, val, '\t')) {
            row.push_back (val);
        }
        if(!array.contains(QString(row.at(2).c_str()))){
            array.push_back(QString(row.at(2).c_str()));
            r_size++;
        }
    }

    for (int i = 1; i < r_size -1;i++) {
        cout << '\t' << array[i].toStdString() << endl;
    }

    return array;
}
