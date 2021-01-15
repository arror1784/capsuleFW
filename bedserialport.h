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
#include "logger.h"

class BedControl;
class PrintScheduler;
union Int2char{

    int32_t int32;
    uint8_t ch[4];

};

typedef struct{

    uint8_t G;
    uint8_t H;
    Int2char A;
    Int2char B;
    Int2char C;
    Int2char M;
    Int2char P;

}commandFormat_t,*commandFormat_P;

typedef struct{
    uint8_t bed;
    uint8_t command;
    uint8_t response;
}ResponseData_t,*ResponseData_p;

class BedSerialport : public QObject
{
    Q_OBJECT
public:
#ifdef TEST_WITHOUT_SERIAL
    BedSerialport(PrintScheduler *sched);
#endif
    BedSerialport(QString portPath, PrintScheduler* sched);

    void setBedControl(BedControl* ctrl);
    void serialClose();
    void serialOpen();

signals:
    void sendToPrintScheduler(char bedChar,int state);
    void abc();

public slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

    void sendCommand(QString command);
    void sendByteCommand(QByteArray buffer);
    QByteArray transData(commandFormat_t );

private:
    QByteArray m_readData;
    QTextStream m_standardOutput;
    QTimer m_timer;

    QByteArray arr;
    QByteArray lastcommand;

    BedControl* _bedControl;
    PrintScheduler* _sched;
    bool m_readAvaiable = true;

    QSerialPort *m_serialPort = nullptr;

public:
    bool getReadAvaiable() const;
    void setReadAvaiable(bool value);

private:
    void parsingResponse(QByteArray array);

};

#endif // BEDSERIALPORT_H
