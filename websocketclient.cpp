#include "websocketclient.h"


WebSocketClient::WebSocketClient(const QUrl url)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    QObject::connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    QObject::connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);
    m_webSocket.open(url);
}

void WebSocketClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    QObject::connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebSocketClient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
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
        this->socket_name = obj["name"].toString();
    }
    m_webSocket.close();
}

