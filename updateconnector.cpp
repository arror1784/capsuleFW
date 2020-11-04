#include "updateconnector.h"

UpdateConnector::UpdateConnector()
{

}

void UpdateConnector::swUpdaterConnect(Updater *swUpdater)
{
    _swUpdater = swUpdater;
    QObject::connect(this,&UpdateConnector::sendToSWGetVersion,_swUpdater,&Updater::getVersion);
    QObject::connect(this,&UpdateConnector::sendToSWGetLastestVersion,_swUpdater,&Updater::getLastestVersion);
    QObject::connect(this,&UpdateConnector::sendToSWCheckUpdate,_swUpdater,&Updater::checkUpdate);
    QObject::connect(this,&UpdateConnector::sendToSWUpdate,_swUpdater,&Updater::update);


    QObject::connect(_swUpdater,&Updater::updateNotice,this,&UpdateConnector::receiveFromSWUpdateNotice);
    QObject::connect(_swUpdater,&Updater::sendVersion,this,&UpdateConnector::receiveFromSWSendVersion);
    QObject::connect(_swUpdater,&Updater::sendLastestVersion,this,&UpdateConnector::receiveFromSWSendLastestVersion);


}

void UpdateConnector::resinUpdaterConnect(ResinUpdater *resinUpdater)
{
    _resinUpdater = resinUpdater;
    QObject::connect(this,&UpdateConnector::sendToResinGetVersion,_resinUpdater,&ResinUpdater::getVersion);
    QObject::connect(this,&UpdateConnector::sendToResinGetLastestVersion,_resinUpdater,&ResinUpdater::getLastestVersion);
    QObject::connect(this,&UpdateConnector::sendToResinCheckUpdate,_resinUpdater,&ResinUpdater::checkUpdate);
    QObject::connect(this,&UpdateConnector::sendToResinUpdate,_resinUpdater,&ResinUpdater::update);


    QObject::connect(_resinUpdater,&ResinUpdater::updateNotice,this,&UpdateConnector::receiveFromResinUpdateNotice);
    QObject::connect(_resinUpdater,&ResinUpdater::sendVersion,this,&UpdateConnector::receiveFromResinSendVersion);
    QObject::connect(_resinUpdater,&ResinUpdater::sendLastestVersion,this,&UpdateConnector::receiveFromResinSendLastestVersion);
}
