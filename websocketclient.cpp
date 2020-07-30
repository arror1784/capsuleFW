#include "websocketclient.h"

#include <QTimer>
#include <QJsonObject>
#include <QMetaObject>

WebSocketClient::WebSocketClient(const QUrl url) :
    _url(url)
{
    if (_debug)
        qDebug() << "WebSocket server:" << url;
    _webSocket = new QWebSocket();
    connect(_webSocket, (void(QWebSocket::*)(QAbstractSocket::SocketError)) &QWebSocket::error, this, &WebSocketClient::error);
    connect(_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);
}

void WebSocketClient::open()
{
    qDebug() << "websocket open";
    _webSocket->open(_url);
}

void WebSocketClient::closed()
{
    qDebug() << "socket disconnected";
    _connected = false;
    QTimer::singleShot(1000, this, &WebSocketClient::open);
}

void WebSocketClient::onConnected()
{
    if (_debug)
        qDebug() << "WebSocket connected";
    QObject::connect(_webSocket, &QWebSocket::textMessageReceived,
            this, &WebSocketClient::onTextMessageReceived);
    _connected = true;
//    m_webSocket->sendTextMessage(QStringLiteral("Hello, world!"));
}

void WebSocketClient::onTextMessageReceived(QString message)
{
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());

    if(!doc.isNull()){
        if(doc.isObject()){
            obj = doc.object();
        }else{
            return;
        }
    }else{
        return;
    }
    if(obj["type"].toString() == "websocket_name"){

        this->_socket_name = obj["name"].toString();
        qDebug() << "websocket_name" << this->_socket_name;

    }else if(obj["type"].toString() == "stateChangeCommand"){
        if(obj["command"] == "start"){
            emit startByWeb(obj["printing_name"].toString(),obj["printing_folder_name"].toString(),obj["material"].toString());
        }
    }
//    _webSocket->close();
}

void WebSocketClient::error(QAbstractSocket::SocketError error){
    qDebug() << "socket connect error" << error;
    _connected = false;
    QTimer::singleShot(1000, this, &WebSocketClient::open);
}

void WebSocketClient::sendStart()
{
    QJsonObject aaa;

    if(!_connected)
        return;

    aaa.insert("type","stateChangeCommand");
    aaa.insert("method","start");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    std::function<void()> func = [this,strJson]() {

        qDebug() << "sendStart";
        _webSocket->sendTextMessage(strJson);
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void WebSocketClient::sendPauseStart()
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","stateChangeCommand");
    aaa.insert("method","pauseStart");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    std::function<void()> func = [this,strJson]() {

        qDebug() << "sendPauseStart";
        _webSocket->sendTextMessage(strJson);
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void WebSocketClient::sendPauseFinish()
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","stateChangeCommand");
    aaa.insert("method","pauseFinish");

    QJsonDocument doc(aaa);

    QString strJson(doc.toJson(QJsonDocument::Compact));

    std::function<void()> func = [this,strJson]() {

        qDebug() << "sendPauseFinish";
        _webSocket->sendTextMessage(strJson);
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void WebSocketClient::sendResume()
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","stateChangeCommand");
    aaa.insert("method","resume");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    std::function<void()> func = [this,strJson](){

        qDebug() << "sendResume";
        _webSocket->sendTextMessage(strJson);
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}

void WebSocketClient::sendFinish()
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","stateChangeCommand");
    aaa.insert("method","finish");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    std::function<void()> func = [this,strJson]() {

        qDebug() << "sendFinish";
        _webSocket->sendTextMessage(strJson);
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}
void WebSocketClient::sendSetTimerOnoff(bool onOff)
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","stateChangeCommand");
    aaa.insert("method","setTimerOnoff");

    aaa.insert("onOff",onOff);

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    std::function<void()> func = [this,strJson]() {

        qDebug() << "sendSetTimerOnOff";
        _webSocket->sendTextMessage(strJson);
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}
void WebSocketClient::sendSetTimerTime()
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","stateChangeCommand");
    aaa.insert("method","setTimerTime");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    std::function<void()> func = [this,strJson]() {

        qDebug() << "sendSetTimerTime";
        _webSocket->sendTextMessage(strJson);
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);
}
void WebSocketClient::sendProgreeUpdate(int progress)
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","progressUpdate");
//    aaa.insert("method","progress");

    aaa.insert("progress",QString::number(progress));

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    std::function<void()> func = [this,strJson]() {

        qDebug() << "sendProgressUpdate";
        _webSocket->sendTextMessage(strJson);
    };

    QMetaObject::invokeMethod(this,func,Qt::AutoConnection);

}

