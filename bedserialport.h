#ifndef BEDSERIALPORT_H
#define BEDSERIALPORT_H

#include <QObject>

//#include <QThread>
#include <QtSerialPort/QSerialPort>

#include <QByteArray>
#include <QTextStream>
#include <QTimer>
#include <QDebug>
#include <QMap>
#include <QMutex>

#include "common.h"
#include <QString>
#include "logger.h"u

union double2char{

    double db;
    uint8_t ch[8];

};

typedef struct{

    uint8_t G;
    uint8_t H;
    double2char A;
    double2char B;
    double2char C;
    double2char M;
    double2char P;
    uint8_t CheckSum;

}commandFormat_t,*commandFormat_P;

class BedSerialport : public QObject
{
    Q_OBJECT
public:
    BedSerialport(QString portPath);

signals:
    void sendSignalToBedControl(char bedChar);
    void sendToPrintScheduler(char bedChar,int state);
    void abc();

public slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

    void sendCommand(char* command);
    void sendByteCommand(QByteArray buffer);
    QByteArray transData(commandFormat_P );

private:
    QSerialPort *m_serialPort = nullptr;
    QByteArray m_readData;
    QTextStream m_standardOutput;
    QTimer m_timer;

    QByteArray arr;
    QByteArray lastcommand;
    QMutex serialMutex;

private:
    void parsingResponse(QByteArray array);

};

#endif // BEDSERIALPORT_H
