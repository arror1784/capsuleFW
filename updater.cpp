#include "updater.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QProcess>
#include <QJsonArray>
#include <QtConcurrent/QtConcurrentRun>

#include "printsetting.h"
#include "resinsetting.h"
#include "version.h"

Updater::Updater():
    _url("https://services.hix.co.kr/setup")
//  ,_downloadUrl("/home/pi/Downloads")
  ,_downloadUrl("/opt/capsuleFW/download")
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished,this, &Updater::requestFinished);
}

void Updater::saveAsFile(QString name,QByteArray ba)
{
    QFile f;
    QString path = _downloadUrl+"/"+name;
    f.setFileName(path);
    if(!f.open(QIODevice::ReadWrite)){
        qDebug() << "Could not open json file to ReadWrite " << path;
        qDebug() << f.errorString();
    }else{
//        qDebug() << "save as file open " << name;
    }
    f.write(ba);
    f.close();
}

void Updater::downloadBin()
{
    _requestAvailable = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_BIN;
        request.setUrl(_url + "/get_file/capsule/" + _binName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::downloadSH()
{
    _requestAvailable = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_SH;
        request.setUrl(_url + "/get_file/capsule/" + _shName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::downloadZIP()
{
    _requestAvailable = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_ZIP;
        request.setUrl(_url + "/get_file/capsule/" + _zipName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::downloadVER()
{
    _requestAvailable = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_VER;
        request.setUrl(_url + "/get_file/capsule/" + _verName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::downloadLIST()
{
    _requestAvailable = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_LIST;
        request.setUrl(_url + "/get_update_manifest/capsule");
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::waitForRequest()
{
    while(!_requestAvailable);
}

void Updater::waitForMCUFirmwareUpdate()
{
    while(!_MCUFirmwareUpdateFinished);
    _MCUFirmwareUpdateFinished = false;
}

void Updater::checkUpdate()
{
    _requestAvailable = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::UPDATE_CHECK;
        request.setUrl(_url + "/get_file/capsule/" + _verName);
        manager->get(request);

    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::update()
{
    _future = QtConcurrent::run([this]() {
        downloadLIST();
        waitForRequest();
        downloadVER();
        waitForRequest();
        if(_MCUFirmwareUpdateAvailable){
            downloadBin();
            waitForRequest();
            _MCUFirmwareUpdateFinished = false;
            emit updateMCUFirmware(_downloadUrl + "/" + _binName);
            waitForMCUFirmwareUpdate();
        }
        //download new update.sh
        downloadSH();
        waitForRequest();
        //download new update file - *.zip
        downloadZIP();
        waitForRequest();
        //run update.sh with root
        QString command = _downloadUrl + "/" + _shName + " " + _downloadUrl + "/" + _zipName + " " + _downloadUrl + " " + _downloadUrl + "/" + _verName;
        qDebug() << "command " << command;
        QProcess::execute("chmod +x " + _downloadUrl + "/" + _shName);
        QProcess::startDetached("bash -c \"echo rasp | sudo -S " + command + " \"");
    });

    return;
}

void Updater::requestFinished(QNetworkReply* reply)
{
    if (reply->error()) {
        emit updateError();
        qDebug() << reply->errorString();
        return;
    }
    QByteArray answer = reply->readAll();
    qDebug() << reply->url();
//    qDebug() << "answer" << answer;

    QJsonDocument jd;
    QJsonObject jo;
    QJsonArray ja;
    QByteArray loadData;

    switch (_requestType) {
        case SWRequestType::UPDATE_CHECK:
            jd = QJsonDocument::fromJson(answer);
            jo = jd.object();
            qDebug() << "current Version : " << Version::GetInstance()->getVersion();
            qDebug() << "update Version : " << jo["version"].toString();
            if(jo["version"].toString() != Version::GetInstance()->getVersion()){
                emit updateAvailable();
            }else{
                emit updateNotAvailable();
            }
            break;
        case SWRequestType::DOWNLOAD_LIST:
            jd = QJsonDocument::fromJson(answer);
            ja = jd.array();
            qDebug() << ja;
            if(ja.contains(_binName)){
                qDebug() << "MCU Firmware update Available";
                _MCUFirmwareUpdateAvailable = true;
            }
            break;
        case SWRequestType::DOWNLOAD_BIN:
            saveAsFile(_binName,answer);
            _MCUFirmwareUpdateAvailable = false;
            break;
        case SWRequestType::DOWNLOAD_SH:
            saveAsFile(_shName,answer);
            break;
        case SWRequestType::DOWNLOAD_ZIP:
            saveAsFile(_zipName,answer);
            break;
        case SWRequestType::DOWNLOAD_VER:
            saveAsFile(_verName,answer);
            break;
        case SWRequestType::DOWNLOAD_ALL:
            qDebug() << "download all";
            break;
        case SWRequestType::NONE:
            qDebug() << "none";
            break;
    }
    _requestType = SWRequestType::NONE;
    _requestAvailable = true;
}

void Updater::MCUFirmwareUpdateFinished()
{
    _MCUFirmwareUpdateFinished = true;
}


