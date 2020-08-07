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

//    void sendStart();
//    void sendPauseStart();
//    void sendPauseFinish();
//    void sendResume();
//    void sendFinish();
//    void sendEnableTimer(bool onOff);
//    void sendSetTimerTime();
//    void sendProgreeUpdate(int progress);

//    void fileSave(QString name,QByteArray hello);

signals:
    void downloadFiles(QString byte);

    void startByWeb(QString filePath,QString material,QJsonObject byte);
    void pauseByWeb();
    void resumeByWeb();
    void finishByWeb();

    void getMaterialListbyWeb();

    void getPrintInfoByWeb();



public slots:
    void updateProgressToWeb(int progress); //update Progress

//    void sendToUIFirstlayerStart();         //For CAL PrintTime
//    void sendToUIFirstlayerFinish();        //For CAL PrintTime

    void changeToPrintToWeb();       //change ui Ready to Print

    void changeToPauseStartToWeb();      //chage ui print to Pause Start
    void changeToPauseFinishToWeb();     //change ui Pause Start to Pause Finish
    void changeToResumeToWeb();          //change ui Pause Finish to Print
    void changeToQuitToWeb();            //change ui all state to Quit

    void changeToPrintFinishToWeb();             //chagne UI state Print To Ready
    void changeToPrintWorkErrorToWeb();          //Error when Printing
    void changeToPrintWorkErrorFinishToWeb();    //change UI State Print To Ready By Error
    void changeToPrintSettingErrorToWeb(int code);       //print setting Error when received print start from UI

    void enableTimer(bool enable);      //for enabel Timer

    void setTotalTime(int time);
    void materialListToWeb(QVariantList name);   //Material List UI must insert Custm resin when resin.json exist

    void getPrintInfoToWeb(QString printerState,QString material, QString fileName,double layerHeight,int elapsedTime,int totalTime,int progress,bool enableTimer);


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
