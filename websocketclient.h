#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QtWebSockets/QtWebSockets>

#include "moodycamel/blockingconcurrentqueue.h"

enum class WSCommand {
    START,
    PAUSE,
    RESUME,
    FINISH,
    SETTIMERONOFF,
    SETTIMERTIME,
    UPDATE
};


class WebSocketClient : public QThread
{
    Q_OBJECT
public:
    WebSocketClient(const QUrl url);

    void sendStart();
    void sendPause();
    void sendResume();
    void sendFinish();
    void sendSetTimerOnoff(bool onOff);
    void sendSetTimerTime(int time);
    void sendProgreeUpdate(int progress);

    void enqueTask(WSCommand);

signals:

private slots:
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

    moodycamel::BlockingConcurrentQueue<WSCommand> _queue;

protected:
    void run()override;

};

#endif // WEBSOCKETCLIENT_H
