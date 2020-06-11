#include "websocketclient.h"

#include <QTimer>
#include <QJsonObject>

WebSocketClient::WebSocketClient(const QUrl url) :
    _url(url)
{
    if (_debug)
        qDebug() << "WebSocket server:" << url;
//    open();
}

void WebSocketClient::run(){

    WSCommand task;
//    while(!_connected)
//        QThread::exec();
//    if(_webSocket != nullptr){

    _webSocket =  new QWebSocket();
    qDebug() << "_webSocket created : " << QThread::currentThread();

//    QObject::connect(_webSocket, (void(QWebSocket::*)(QAbstractSocket::SocketError)) &QWebSocket::error, this, &WebSocketClient::error);
    QObject::connect(_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    QObject::connect(_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);

    _webSocket->open(_url);

    QThread::exec();

    qDebug() <<"_webSocket" << _webSocket->thread()->currentThread();
    _webSocket->sendTextMessage("{\"type\":\"fuck\"}");

    qDebug() << "websocketclient: " << QThread::currentThread();

    QThread::exec();

    while(1){
        _queue.wait_dequeue(task);
        qDebug()<<"deque";
        switch (task) {
            case WSCommand::START:
                QJsonObject aaa;
                qDebug() << "fuckfuck";

                if(!_connected)
                    break;

                aaa.insert("type","progress");
                aaa.insert("method","start");

                QJsonDocument doc(aaa);
                QString strJson(doc.toJson(QJsonDocument::Compact));

                qDebug() << "sendStart: " << QThread::currentThread();
                _webSocket->sendTextMessage(strJson);
                QThread::exec();
                break;
        }
    }
//    while(true)
//        QThread::exec();
}

void WebSocketClient::sendStart()
{
//    std::function<void()> fn = [this](){
//        QJsonObject aaa;
//        qDebug() << "fuckfuck";

//        if(!_connected)
//            return;

//        aaa.insert("type","progress");
//        aaa.insert("method","start");

//        QJsonDocument doc(aaa);
//        QString strJson(doc.toJson(QJsonDocument::Compact));

//        qDebug() << "sendStart: " << QThread::currentThread();
//        _webSocket->sendTextMessage(strJson);
//    };
    _queue.enqueue(WSCommand::START);
}

void WebSocketClient::sendPause()
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","progress");
    aaa.insert("method","setTimerTime");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::sendResume()
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","progress");
    aaa.insert("method","resume");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::sendFinish()
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","progress");
    aaa.insert("method","finish");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::sendSetTimerOnoff(bool onOff)
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","progress");
    aaa.insert("method","setTimerOnoff");

    aaa.insert("onOff",onOff);

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::sendSetTimerTime(int time)
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","progress");
    aaa.insert("method","setTimerTime");

    aaa.insert("startTime",QString::number(time));

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::sendProgreeUpdate(int progress)
{
    QJsonObject aaa;
    if(!_connected)
        return;

    aaa.insert("type","progress");
    aaa.insert("progress",QString::number(progress));

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
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
    quit();
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
    }
//    _webSocket->close();
}

void WebSocketClient::error(QAbstractSocket::SocketError error){
    qDebug() << "socket connect error" << error;
    _connected = false;
    QTimer::singleShot(1000, this, &WebSocketClient::open);
}
