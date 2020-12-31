#pragma once



#include <QObject>
#include <QVariantList>
#include <QList>
#include <QMap>
#include <thread>

#include "wifiinfo.h"

#ifdef __arm__
#define WPA_CTRL_INTERFACE "/var/run/wpa_supplicant/wlan0"
#else
#define WPA_CTRL_INTERFACE "/var/run/wpa_supplicant/wlp3s0"
#endif



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

    void wifiConnectError();

public slots:
    void networkScan();

    int networkCount();
    WifiInfo* getNetwork(int index);

    bool networkConnect(QString ssid,QString bssid,QString passwd,int networkID);
    bool networkConnect(int id);

    bool networkDisconnect();
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

    int networkAdd();
    void networkSelect(int id);
    void networkEnable(int id);
    void networkDisable(int id);
    void networkSaveConfig();
    void networkSet(int id,std::string key,std::string value);

    int wpa_ctrl_cmd(struct wpa_ctrl *ctrl, const char *cmd, char *buf);

    QList<WifiInfo*> _wifiList;

    std::thread th;

    wpa_ctrl* _ctrl;
    wpa_ctrl* _ctrl_event;
    
    QString _currentSSID;
    QString _ctrlPath;

    bool _connected = false;
    int _connectID = -1;
};



