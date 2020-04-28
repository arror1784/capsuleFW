#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QtWebSockets/QtWebSockets>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    WebSocketClient(const QUrl url);

signals:
    void closed();

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;

};

#endif // WEBSOCKETCLIENT_H
