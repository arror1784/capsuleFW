#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QtWebSockets/QtWebSockets>

enum class WSCommand {
    START,
    PAUSE,
    RESUME,
    FINISH,
    SETTIMERONOFF,
    SETTIMERTIME,
    UPDATE
};


class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    WebSocketClient(const QUrl url);

    void sendStart();
    void sendPauseStart();
    void sendPauseFinish();
    void sendResume();
    void sendFinish();
    void sendSetTimerOnoff(bool onOff);
    void sendSetTimerTime();
    void sendProgreeUpdate(int progress);

signals:
    void startByWeb(QString printName,QString filePath,QString material);

public slots:

    void open();
    void closed();

    void onConnected();
    void onTextMessageReceived(QString message);
    void error(QAbstractSocket::SocketError error);

private:
    QWebSocket *_webSocket;
    QString _socket_name;
    QUrl _url;
    bool _debug = true;
    bool _connected = false;

};

#endif // WEBSOCKETCLIENT_H
