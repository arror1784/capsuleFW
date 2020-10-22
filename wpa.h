#pragma once



#include <QObject>
#include <QVariantList>
#include <QList>
#include <QMap>
#include <thread>

#include "wifiinfo.h"

#define WPA_CTRL_INTERFACE "/var/run/wpa_supplicant/wlx88366cfb28d9"
//#define WPA_CTRL_INTERFACE "/var/run/wpa_supplicant/wlan0"


enum class WIFIInfoType{
    BSSID=0,
    FREQ=1,
    SIGLEV=2,
    FLAGS=3,
    SSID=4,
};
enum class NetworkInfoType{
    ID=0,
    BSSID=1,
    SSID=2,
    FREQ=3,
    SIGLEV=4,
    FLAGS=5,
};

class WPA : public QObject
{
    Q_OBJECT

public:
    WPA();
    WPA(const char* ctrl_path);

    void selectNetwork(QString ssid, QString pwd);
    void runEvent();

signals:
    void networkListUpdate();
    void currentStateChange();

    void connectedChange(bool connected);

    void refreshAvailable();

public slots:
    void networkScan();

    int networkCount();
    WifiInfo* getNetwork(int index);

    bool networkConnect(QString ssid,QString bssid,QString passwd,int networkID);
    bool networkConnect(QString ssid,QString bssid,QString passwd);
    bool networkConnect(int id);

    bool networkConnect(QString ssid,QString bssid,int networkID);
    bool networkConnect(QString ssid,QString bssid);

    bool networkDisconnect();
    void networkDelete(QString ssid);
    void networkDelete(int id);

    void checkNetworkConnect();

    QString currentSSID() const;

private:
    void ctrlConnect();
    void wpa_ctrl_event();

    void clearList();

    void parseWifiInfo(); //scan_result
    void parseNetworkInfo(); //saved_network_list

    void checkConnected();

    int wpa_ctrl_cmd(struct wpa_ctrl *ctrl, char *cmd, char *buf);

    QList<WifiInfo*> _wifiList;

    std::thread th;

    wpa_ctrl* _ctrl;
    wpa_ctrl* _ctrl_event;
    
    QString _currentSSID;
    QString _ctrlPath;

    bool _connected = false;
};



