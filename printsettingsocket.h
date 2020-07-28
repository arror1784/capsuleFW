#ifndef PRINTSETTINGSOCKET_H
#define PRINTSETTINGSOCKET_H

#include <QObject>
#include <QUrl>
#include <QAbstractSocket>
#include <QWebSocket>
#include <memory>
#include <QMetaObject>
class PrintSettingSocket : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
//    Q_PROPERTY(bool fileValid READ isFileValid NOTIFY fileValidChanged)
//    Q_PROPERTY(QString fileErrorMessage READ fileErrorMessage WRITE setFileErrorMessage NOTIFY fileErrorMessageChanged)
//    Q_PROPERTY(bool treatAsImage READ treatAsImage WRITE setTreatAsImage NOTIFY treatAsImageChanged)
public:
    explicit PrintSettingSocket(QObject *parent = nullptr);
    virtual ~PrintSettingSocket();
signals:
    void socketDisconnect();
    void socketError();

public slots:
    void socketOpen();
    void socketClose();

    void onWebSocketClosed();
    void onWebSocketConnected();
    void onTextMessageReceived(QString message);
    void onWebSocketError(QAbstractSocket::SocketError error);

protected:
    QMetaObject::Connection _disconnectConnToken;
    QMetaObject::Connection _errorConnToken;
    QUrl _url;
    std::unique_ptr<QWebSocket> _webSocket;
//    bool _opened = false;

};

#endif // PRINTSETTINGSOCKET_H
