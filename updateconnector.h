#ifndef UPDATECONNECTOR_H
#define UPDATECONNECTOR_H

#include <QObject>
#include <updater.h>
#include <resinupdater.h>

class UpdateConnector : public QObject
{
    Q_OBJECT
public:
    UpdateConnector();

    void swUpdaterConnect(Updater* swUpdater);
    void resinUpdaterConnect(ResinUpdater* resinUpdater);
signals:
    void sendToSWGetVersion();
    void sendToSWGetLastestVersion();
    void sendToSWCheckUpdate();
    void sendToSWUpdate();

    void sendToQmlSWUpdateNotice(QString state);
    void sendToQmlSWSendVersion(QString version);
    void sendToQmlSWSendLastestVersion(QString version);


    void sendToResinGetVersion();
    void sendToResinGetLastestVersion();
    void sendToResinCheckUpdate();
    void sendToResinUpdate();

    void sendToQmlResinUpdateNotice(QString state);
    void sendToQmlResinSendVersion(QString version);
    void sendToQmlResinSendLastestVersion(QString version);


public slots:
    void receiveFromQmlSWGetVersion(){emit sendToSWGetVersion();}
    void receiveFromQmlSWGetLastestVersion(){emit sendToSWGetLastestVersion();}
    void receiveFromQmlSWCheckUpdate(){emit sendToSWCheckUpdate();}
    void receiveFromQmlSWUpdate(){emit sendToSWUpdate();}

    void receiveFromSWUpdateNotice(QString state){emit sendToQmlSWUpdateNotice(state);}
    void receiveFromSWSendVersion(QString version){emit sendToQmlSWSendVersion(version);}
    void receiveFromSWSendLastestVersion(QString version){emit sendToQmlSWSendLastestVersion(version);}




    void receiveFromQmlResinGetVersion(){emit sendToResinGetVersion();}
    void receiveFromQmlResinGetLastestVersion(){emit sendToResinGetLastestVersion();}
    void receiveFromQmlResinCheckUpdate(){emit sendToResinCheckUpdate();}
    void receiveFromQmlResinUpdate(){emit sendToResinUpdate();}

    void receiveFromResinUpdateNotice(QString state){emit sendToQmlResinUpdateNotice(state);}
    void receiveFromResinSendVersion(QString version){emit sendToQmlResinSendVersion(version);}
    void receiveFromResinSendLastestVersion(QString version){emit sendToQmlResinSendLastestVersion(version);}

private:
    Updater* _swUpdater;
    ResinUpdater* _resinUpdater;


};

#endif // UPDATECONNECTOR_H
