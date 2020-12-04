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
    void sendToSWCheckUpdate();
    void sendToSWUpdate();
    void sendToSWCheckUpdateUSB(QString path);
    void sendToSWUpdateUSB(QString path);

#ifdef MCU_UPDATE_TEST
    void sendToSWMCUUpdate(QString path);
#endif

    void sendToQmlSWUpdateNotice(QString state,QString mode);
    void sendToQmlSWSendVersion(QString version);
    void sendToQmlSWSendLastestVersion(QString version);


    void sendToResinGetVersion();
    void sendToResinCheckUpdate();
    void sendToResinUpdate();
    void sendToResinCheckUpdateUSB(QString path);
    void sendToResinUpdateUSB(QString path);

    void sendToQmlResinUpdateNotice(QString state,QString mode);
    void sendToQmlResinSendVersion(QString version);
    void sendToQmlResinSendLastestVersion(QString version);


public slots:
    void receiveFromQmlSWGetVersion(){emit sendToSWGetVersion();}
    void receiveFromQmlSWCheckUpdate(){emit sendToSWCheckUpdate();}
    void receiveFromQmlSWUpdate(){emit sendToSWUpdate();}
    void receiveFromQmlSWCheckUpdateUSB(QString path){emit sendToSWCheckUpdateUSB(path);}
    void receiveFromQmlSWUpdateUSB(QString path){emit sendToSWUpdateUSB(path);}

    void receiveFromSWUpdateNotice(QString state,QString mode){emit sendToQmlSWUpdateNotice(state,mode);}
    void receiveFromSWSendVersion(QString version){emit sendToQmlSWSendVersion(version);}
    void receiveFromSWSendLastestVersion(QString version){emit sendToQmlSWSendLastestVersion(version);}




    void receiveFromQmlResinGetVersion(){emit sendToResinGetVersion();}
    void receiveFromQmlResinCheckUpdate(){emit sendToResinCheckUpdate();}
    void receiveFromQmlResinUpdate(){emit sendToResinUpdate();}
    void receiveFromQmlResinCheckUpdateUSB(QString path){emit sendToResinCheckUpdateUSB(path);}
    void receiveFromQmlResinUpdateUSB(QString path){emit sendToResinUpdateUSB(path);}

    void receiveFromResinUpdateNotice(QString state,QString mode){emit sendToQmlResinUpdateNotice(state,mode);}
    void receiveFromResinSendVersion(QString version){emit sendToQmlResinSendVersion(version);}
    void receiveFromResinSendLastestVersion(QString version){emit sendToQmlResinSendLastestVersion(version);}

private:
    Updater* _swUpdater;
    ResinUpdater* _resinUpdater;


};

#endif // UPDATECONNECTOR_H
