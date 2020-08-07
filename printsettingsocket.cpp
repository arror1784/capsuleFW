#include "printsettingsocket.h"

#include <QWebSocket>

void qDeleteLater(QWebSocket* obj)
{
    obj->deleteLater();
}

PrintSettingSocket::PrintSettingSocket(QObject *parent)
    : QObject(parent)
    ,_url(QUrl(QStringLiteral("ws://localhost:8000/ws/setting")))
{

    //    _webSocket = new QWebSocket();
}

PrintSettingSocket::~PrintSettingSocket()
{

}

void PrintSettingSocket::socketOpen()
{
    _webSocket.reset(new QWebSocket());

    _errorConnToken = connect(_webSocket.get(), QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &PrintSettingSocket::onWebSocketError);
    _disconnectConnToken = connect(_webSocket.get(), &QWebSocket::disconnected, this, &PrintSettingSocket::onWebSocketClosed);

    connect(_webSocket.get(), &QWebSocket::connected, this, &PrintSettingSocket::onWebSocketConnected);
    _webSocket->open(_url);
}

void PrintSettingSocket::socketClose()
{
    if(_webSocket)
    {
        qDebug() << "socket close";
        QObject::disconnect(_errorConnToken);
        QObject::disconnect(_disconnectConnToken);
        _webSocket->close();
        _webSocket->deleteLater();
        _webSocket.release();
    }
}

void PrintSettingSocket::onWebSocketClosed()
{
//    _opened = false;
    qDebug() << "close by server";
    _webSocket.release();
    emit socketDisconnect();
}

void PrintSettingSocket::onWebSocketConnected()
{
    QObject::connect(_webSocket.get(), &QWebSocket::textMessageReceived,
            this, &PrintSettingSocket::onTextMessageReceived);
//    _opened = true;
}

void PrintSettingSocket::onTextMessageReceived(QString message)
{
    qDebug() << message;
    return;
}

void PrintSettingSocket::onWebSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << error;
//    _opened = false;
    _webSocket.release();
    emit socketError();
}
