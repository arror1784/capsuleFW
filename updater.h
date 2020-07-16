#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QUrl>

class Updater
{
public:
    Updater();
    bool checkForUpdate();

    int update();

private:
    QUrl _url;

};

#endif // UPDATER_H
