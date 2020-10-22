#ifndef WIFIINFO_H
#define WIFIINFO_H

#include <QObject>

class WifiInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int networkID READ getNetworkID )
    Q_PROPERTY(QString ssid READ getSsid)
    Q_PROPERTY(QString bssid READ getBssid)
    Q_PROPERTY(bool flags READ getFlags)
    Q_PROPERTY(int freq READ getFreq)
    Q_PROPERTY(int signal_level READ getSignal_level)
    Q_PROPERTY(bool saved READ getSaved)
    Q_PROPERTY(int connected READ getConnected)
public:
    explicit WifiInfo(QObject *parent = nullptr);
    WifiInfo(int networkID, QString ssid, QString bssid, bool flags, int freq, int signal_level, bool saved,bool connected);
//    WifiInfo(const WifiInfo& other);
//    ~WifiInfo();


    int networkID;
    QString ssid;
    QString bssid;
    bool flags;
    int freq;
    int signal_level;

    bool saved = false;
    bool connected = false;

signals:

public slots:

    int getNetworkID() const;
    void setNetworkID(int value);

    QString getSsid() const;
    void setSsid(const QString &value);

    QString getBssid() const;
    void setBssid(const QString &value);

    bool getFlags() const;
    void setFlags(bool &value);

    int getFreq() const;
    void setFreq(int value);

    int getSignal_level() const;
    void setSignal_level(int value);

    bool getSaved() const;
    void setSaved(bool value);

    bool getConnected() const;
    void setConnected(bool value);

};

Q_DECLARE_METATYPE(WifiInfo*)

#endif // WIFIINFO_H
