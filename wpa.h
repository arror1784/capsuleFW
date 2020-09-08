#ifndef WPA_H
#define WPA_H

#include "wpa_ctrl/wpa_ctrl.h"

#include <QObject>
#include <thread>

//#define WPA_CTRL_INTERFACE "/var/run/wpa_supplicant/wlx88366cfb28d9"
#define WPA_CTRL_INTERFACE "/var/run/wpa_supplicant/wlan0"


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

    void refreshAvailable();

public slots:
    void networkScan();
    QStringList networkList();
    QStringList apList();

    bool networkConnect(QString ssid,QString passwd);
    bool networkDisconnect();
    void networkDelete(QString ssid);
    QString currentSSID() const;

private:
    void ctrlConnect();
    void wpa_ctrl_event();

    void refresh();

    QStringList parse_to_wifi_name(char *buff);
    QStringList parse_to_network_list(char *buff);
    int wpa_ctrl_cmd(struct wpa_ctrl *ctrl, char *cmd, char *buf);


    std::thread th;

    wpa_ctrl* _ctrl;
    wpa_ctrl* _ctrl_event;
    
    QString _currentSSID;
    QString _ctrlPath;
};



#endif // WPA_H
