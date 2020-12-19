#include "updater.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QProcess>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtConcurrent/QtConcurrentRun>

#include <chrono>
#include <thread>

#include "printersetting.h"
#include "resinsetting.h"
#include "version.h"
#include "zip/zip.h"

Updater::Updater():
    _url("https://services.hix.co.kr/setup")
//  ,_downloadUrl("/home/pi/Downloads")
  ,_downloadUrl("/opt/capsuleFW/download")
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished,this, &Updater::requestFinished);
    checkUpdate();
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
    _networkError = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_BIN;
        request.setUrl(_url + "/get_file/C10/" + _binName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::downloadSH()
{
    _requestAvailable = false;
    _networkError = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_SH;
        request.setUrl(_url + "/get_file/C10/" + _shName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::downloadZIP()
{
    _requestAvailable = false;
    _networkError = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_ZIP;
        request.setUrl(_url + "/get_file/C10/" + _zipName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::downloadVER()
{
    _requestAvailable = false;
    _networkError = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_VER;
        request.setUrl(_url + "/get_file/C10/" + _verName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::downloadLIST()
{
    _requestAvailable = false;
    _networkError = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::DOWNLOAD_LIST;
        request.setUrl(_url + "/get_update_manifest/C10");
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::checkUpdate()
{
    _requestAvailable = false;
    _networkError = false;
    std::function<void()> func = [this]() {
        _requestType = SWRequestType::UPDATE_CHECK;
        request.setUrl(_url + "/get_file/C10/" + _verName);
        manager->get(request);
    };
    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void Updater::checkUpdateUSB(QString path)
{
    auto spath = path.toStdString();

    try {

        miniz_cpp::zip_file file(spath);
        auto testValue = file.testzip();
        if(!testValue.first){
            emit updateNotice("error","usb");
            return;
        }
        if(!file.has_file("USB")){
            emit updateNotice("error","usb");
        }
        if(!file.has_file("SW")){
            emit updateNotice("error","usb");
        }
        QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(file.read("version.json")));
        QJsonObject object = doc.object();

        auto lastestVersion = object["version"].toString();

        if(lastestVersion != Version::getInstance().version){
            emit updateNotice("available","usb");;
        }else{
            emit updateNotice("notAvailable","usb");
        }
        emit sendLastestVersion(lastestVersion);

    } catch (std::exception e) {
        emit updateNotice("error","usb");
    }
}

void Updater::update()
{
    qDebug() << "update start";
    _future = std::async([this]() {
        downloadLIST();
        qDebug() << "download List";
        if(waitForRequest()){
            emit updateNotice("error","network");
            return;
        }
        downloadVER();
        if(waitForRequest()){
            emit updateNotice("error","network");
            return;
        }
        if(_MCUFirmwareUpdateAvailable){
            downloadBin();
            if(waitForRequest()){
                emit updateNotice("error","network");
                return;
            }
            _MCUFirmwareUpdateFinished = false;
            emit updateMCUFirmware(_downloadUrl + "/" + _binName);
            waitForMCUFirmwareUpdate();
        }
        //download new update.sh
        downloadSH();
        if(waitForRequest()){
            emit updateNotice("error","network");
            return;
        }
        //download new update file - *.zip
        downloadZIP();
        if(waitForRequest()){
            emit updateNotice("error","network");
            return;
        }
        //run update.sh with root
#ifdef __arm__
        updateCommandExcute();
#else
        emit updateNotice("finish","network");
#endif
    });

    return;
}

void Updater::updateUSB(QString path)
{
    auto spath = path.toStdString();

    try {

        miniz_cpp::zip_file file(spath);
        auto testValue = file.testzip();
        if(!testValue.first){
            emit updateNotice("error","usb");
            return;
        }

        file.extractall(_downloadUrl.toStdString());

#ifdef __arm__
        updateCommandExcute();
#else
        emit updateNotice("finish","network");
#endif
    } catch (std::exception e) {
        emit updateNotice("error","usb");
    }
    //testzip
    //check version
    //update by USB
}

void Updater::updateCommandExcute()
{
    QString command = _downloadUrl + "/" + _shName + " " + _downloadUrl + "/" + _zipName + " " + _downloadUrl + " " + _downloadUrl + "/" + _verName;
    QProcess::execute("chmod +x " + _downloadUrl + "/" + _shName);
    QProcess::startDetached("bash -c \"echo rasp | sudo -S " + command + " \"");
}

int Updater::waitForRequest()
{
    std::unique_lock<std::mutex> lk(_cv_m);
    _cv.wait(lk,[this]{return this->_requestAvailable;});
    if(_networkError){
        return -1;
    }else{
        return 0;
    }
}

void Updater::waitForMCUFirmwareUpdate()
{
    std::unique_lock<std::mutex> lk(_cv_mcu_m);
    _cv_mcu.wait(lk,[this]{return this->_MCUFirmwareUpdateFinished;});
}

#ifdef MCU_UPDATE_TEST
void Updater::MCUUpdate(QString path)
{
    _MCUFirmwareUpdateFinished = false;
    emit updateMCUFirmware(path);
    waitForMCUFirmwareUpdate();
}
#endif

void Updater::getVersion()
{
    emit sendVersion(Version::getInstance().version);
}

void Updater::requestFinished(QNetworkReply* reply)
{
    if (reply->error()) {
        emit updateNotice("error","network");
        _networkError = true;
        _requestAvailable = true;
        _cv.notify_all();
        qDebug() << reply->errorString();
        return;
    }
    QByteArray answer = reply->readAll();

    QJsonDocument jd;
    QJsonObject jo;
    QJsonArray ja;
    QByteArray loadData;
    QString lastestVersion;
    qDebug() << reply->url();

    switch (_requestType) {
        case SWRequestType::UPDATE_CHECK:
            jd = QJsonDocument::fromJson(answer);
            jo = jd.object();
            lastestVersion = jo["version"].toString();
            if(jo["version"].toString() != Version::getInstance().version){
                emit updateNotice("available","network");;
            }else{
                emit updateNotice("notAvailable","network");
            }
            emit sendLastestVersion(lastestVersion);
            break;
        case SWRequestType::DOWNLOAD_LIST:
            jd = QJsonDocument::fromJson(answer);
            ja = jd.array();
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
    _networkError = false;
    _cv.notify_all();
}

void Updater::MCUFirmwareUpdateFinished()
{
    _MCUFirmwareUpdateFinished = true;
    _cv_mcu.notify_all();
}


