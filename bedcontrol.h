#ifndef BEDCONTROL_H
#define BEDCONTROL_H

#include <QThread>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QMutex>
#include <QDateTime>

#include "common.h"

class BedSerialport;
class PrintScheduler;
class BedControl: public QObject
{
    Q_OBJECT
public:
    BedControl(char bedChar,BedSerialport* bedSerialPort,PrintScheduler* sched);

    void setAccleSpeed(int val,int mode);
    void setDecelSpeed(int val,int mode);

    void setUpAccleSpeed(int val);
    void setUpDecelSpeed(int val);
    void setDownAccleSpeed(int val);
    void setDownDecelSpeed(int val);

    void setMaxSpeed(int val);
    void setInitSpeed(int val);

    void printDelay();
    void autoHome();
    void moveUpCommand();
    void moveUpCommandMax();
    void moveDownCommand();
    void moveDownCommandMin();
    void moveReadyPosition();

    void setCuringTime(const int value);
    void setBedCuringTime(const int value);
    void setZHopHeightTime(const int value);
    void setLayerHeightTime(const int value);

    void setLedOffset(int value);

signals:
    void sendCommand(QString command);
    void sendByteCommand(QByteArray buffer);
    void sendToPrintScheduler(char bedChar,int state);

public slots:
    void receiveFromBedSerialPort();

public:
    void receiveFromPrintScheduler(int receive);


    char bedChar;
    int maxHeight = 0;
    int LayerHeight = 100;
    int ZHopHeight = 10000;

    int printingState = 0;

    int defaultHeight = 68000; //100//102//97600//102700//102400

    unsigned int layerDelay = 1000;
    unsigned int curingTime = 2000;

    unsigned int bedCuringTime = 15000;

private:

    int _maxSpeed = 150;
    int _InitSpeed = 20;

    int _upAccelSpeed = 10;
    int _upDecelSpeed = 10;
    int _downAccelSpeed = 10;
    int _downDecelSpeed = 10;

    int ledOffset = 1000;

    int bedState = PRINT_MOVE_NULL;

//    double currentPosition = 0.0;
//    double pauseMoveMilli = 0.0;

    QTimer m_timer;
    //int motor_accel;
    //int motor_deccel;

    PrintScheduler *_sched;
    BedSerialport *_bedSerialPort = nullptr;
    QMutex bedControlLock;

};

#endif // BEDCONTROL_H
