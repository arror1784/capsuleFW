#ifndef WIFIINFO_H
#define WIFIINFO_H

#include <QObject>

class WifiInfo : public QObject
{
    Q_OBJECT
public:
    explicit WifiInfo(QObject *parent = nullptr);
    WifiInfo(int networkID, QString ssid, QString bssid, QString flags, int freq, int signal_level, bool saved);
//    WifiInfo(const WifiInfo& other);
//    ~WifiInfo();

    int networkID;
    QString ssid;
    QString bssid;
    QString flags;
    int freq;
    int signal_level;

    bool saved;

signals:

public slots:

    int getNetworkID() const;
    void setNetworkID(int value);

    QString getSsid() const;
    void setSsid(const QString &value);

    QString getBssid() const;
    void setBssid(const QString &value);

    QString getFlags() const;
    void setFlags(const QString &value);

    int getFreq() const;
    void setFreq(int value);

    int getSignal_level() const;
    void setSignal_level(int value);

    bool getSaved() const;
    void setSaved(bool value);


};

Q_DECLARE_METATYPE(WifiInfo*)

#endif // WIFIINFO_H
