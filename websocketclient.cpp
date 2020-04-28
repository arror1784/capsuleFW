#include "websocketclient.h"


WebSocketClient::WebSocketClient(const QUrl url)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    QObject::connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    QObject::connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);
    m_webSocket.open(url);
}
//! [constructor]

//! [onConnected]
void WebSocketClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    QObject::connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebSocketClient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}
//! [onConnected]

//! [onTextMessageReceived]
void WebSocketClient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    m_webSocket.close();
}

