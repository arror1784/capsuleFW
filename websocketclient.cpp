#include "websocketclient.h"

#include <QTimer>
#include <QJsonObject>
#include <QMetaObject>
#include "productsetting.h"

WebSocketClient::WebSocketClient(const QUrl url) :
    _url(url)
{
    if (_debug)
        qDebug() << "WebSocket server:" << url;
    _webSocket = new QWebSocket();
    connect(_webSocket, (void(QWebSocket::*)(QAbstractSocket::SocketError)) &QWebSocket::error, this, &WebSocketClient::error);
    connect(_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);
    connect(_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
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
    _connected = true;
//    m_webSocket->sendTextMessage(QStringLiteral("Hello, world!"));
}

void WebSocketClient::onTextMessageReceived(QString message)
{
    QJsonObject obj;
    QJsonObject args;

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

    if(obj["method"].toString() == "listMaterialName"){
        emit getMaterialListbyWeb();

    }else if(obj["method"].toString() == "print"){
        args = obj["arg"].toObject();
        QVariantList arg;
        arg.push_back(args["selectedFilename"].toString());
        arg.push_back(args["selectedMaterial"].toString());
        arg.push_back(args["printFiles"].toObject());
        emit startByWeb(arg);
    }else if(obj["method"].toString() == "printInfo"){
        emit getPrintInfoByWeb();

    }else if(obj["method"].toString() == "changeState"){
        QString state = obj["arg"].toString();
        if(state == "pause"){
//            emit pauseByWeb();
            emit changeStateByWeb("pause");
        }else if(state == "resume"){
//            emit resumeByWeb();
            emit changeStateByWeb("resume");
        }else if(state == "quit"){
//            emit finishByWeb();
            emit changeStateByWeb("finish");
        }

    }else if(obj["method"].toString() == "getProductName"){
        setProductName(ProductSetting::getInstance().productStr);
    }
}

void WebSocketClient::error(QAbstractSocket::SocketError error){
    _connected = false;
    QTimer::singleShot(1000, this, &WebSocketClient::open);
}

void WebSocketClient::updateProgressToWeb(int progress){
    QJsonObject aaa;

    if(!_connected)
        return;

    aaa.insert("method","updateProgress");
    aaa.insert("arg",progress);

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}
void WebSocketClient::changeToPrintToWeb()
{
    QJsonObject aaa;
    QJsonObject bbb;

    if(!_connected)
        return;

    aaa.insert("method","changeState");
    aaa.insert("arg","print");

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::changeToStateToWeb(QString state)
{
    QJsonObject aaa;

    if(!_connected)
        return;

    aaa.insert("method","changeState");

    if(state == "pauseStart"){
        aaa.insert("arg","pauseStart");

        QJsonDocument doc(aaa);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        _webSocket->sendTextMessage(strJson);

    }else if(state == "pauseFinish"){
        aaa.insert("arg","pause");

        QJsonDocument doc(aaa);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        _webSocket->sendTextMessage(strJson);

    }else if(state == "resume"){
        aaa.insert("arg","resume");

        QJsonDocument doc(aaa);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        _webSocket->sendTextMessage(strJson);

    }else if(state == "quit"){
        aaa.insert("arg","quit");

        QJsonDocument doc(aaa);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        _webSocket->sendTextMessage(strJson);

    }else if(state == "printFinish"){
        aaa.insert("arg","finish");

        QJsonDocument doc(aaa);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        _webSocket->sendTextMessage(strJson);

    }else if(state == "printError"){
        aaa.insert("arg","error");

        QJsonDocument doc(aaa);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        _webSocket->sendTextMessage(strJson);

    }else if(state == "printErrorFinish"){
        aaa.insert("arg","errorFinish");

        QJsonDocument doc(aaa);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        _webSocket->sendTextMessage(strJson);

    }else if(state == "unlock"){
        aaa.insert("arg","unlock");

        QJsonDocument doc(aaa);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        _webSocket->sendTextMessage(strJson);
    }
}

void WebSocketClient::changeToPrintSettingErrorToWeb(int code)
{
    QJsonObject aaa;

    if(!_connected)
        return;

    aaa.insert("method","printSettingError");
    aaa.insert("arg",code);

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::enableTimer(bool enable)
{
    QJsonObject aaa;

    if(!_connected)
        return;

    aaa.insert("method","enableTimer");
    aaa.insert("arg",enable);

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::setTotalTime(int time)
{
    QJsonObject aaa;

    if(!_connected)
        return;

    aaa.insert("method","setTotalTime");
    aaa.insert("arg",time);

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}
void WebSocketClient::materialListToWeb(QVariantList name)
{
    QJsonObject aaa;

    if(!_connected)
        return;

    aaa.insert("method","listMaterialName");
    aaa.insert("arg",QJsonArray::fromVariantList(name));

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::getPrintInfoToWeb(QString printerState, QString material, QString fileName, double layerHeight, int elapsedTime, int totalTime, int progress,bool enableTimer)
{
    QJsonObject aaa;

    QJsonObject bbb;

    bbb.insert("state",printerState);
    bbb.insert("material",material);
    bbb.insert("fileName",fileName);
    bbb.insert("layerHeight",layerHeight);
    bbb.insert("elapsedTime",elapsedTime);
    bbb.insert("totalTime",totalTime);
    bbb.insert("progress",progress);
    bbb.insert("enableTimer",enableTimer);

    if(!_connected)
        return;

    aaa.insert("method","printInfo");
    aaa.insert("arg",bbb);

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

void WebSocketClient::setProductName(QString name)
{
    QJsonObject aaa;

    if(!_connected)
        return;

    aaa.insert("method","setProductName");
    aaa.insert("arg",name);

    QJsonDocument doc(aaa);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    _webSocket->sendTextMessage(strJson);
}

