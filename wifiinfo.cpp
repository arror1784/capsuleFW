#include "wifiinfo.h"

WifiInfo::WifiInfo(QObject *parent) : QObject(parent)
{

}

WifiInfo::WifiInfo(int networkID, QString ssid, QString bssid, QString flags, int freq, int signal_level, bool saved):
    networkID(networkID),ssid(ssid),bssid(bssid),flags(flags),freq(freq),signal_level(signal_level),saved(saved)
{

}

bool WifiInfo::getSaved() const
{
    return saved;
}

void WifiInfo::setSaved(bool value)
{
    saved = value;
}

int WifiInfo::getSignal_level() const
{
    return signal_level;
}

void WifiInfo::setSignal_level(int value)
{
    signal_level = value;
}

int WifiInfo::getFreq() const
{
    return freq;
}

void WifiInfo::setFreq(int value)
{
    freq = value;
}

QString WifiInfo::getFlags() const
{
    return flags;
}

void WifiInfo::setFlags(const QString &value)
{
    flags = value;
}

QString WifiInfo::getBssid() const
{
    return bssid;
}

void WifiInfo::setBssid(const QString &value)
{
    bssid = value;
}

QString WifiInfo::getSsid() const
{
    return ssid;
}

void WifiInfo::setSsid(const QString &value)
{
    ssid = value;
}

int WifiInfo::getNetworkID() const
{
    return networkID;
}

void WifiInfo::setNetworkID(int value)
{
    networkID = value;
}
