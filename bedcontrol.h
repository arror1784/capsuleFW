#ifndef BEDCONTROL_H
#define BEDCONTROL_H

#include <QThread>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QMutex>
#include <QDateTime>

#include "common.h"
#include "bedserialport.h"

class BedControl : public QThread
{
    Q_OBJECT
public:
    BedControl(char bedChar,BedSerialport* bedSerialPort);
    virtual void run();

    void (BedControl::*current_function)() = nullptr;

    void setAccleSpeed(int val);
    void setDecelSpeed(int val);
    void setMaxSpeed(int val);
    void setMinSpeed(int val);

    void printDelay();
    void autoHome();
    void moveUpCommand();
    void moveUpCommandMax();
    void moveDownCommand();
    void moveDownCommandMin();

    void setCuringTime(const int value);
    void setBedCuringTime(const int value);
    void setZHopHeightTime(const int value);
    void setLayerHeightTime(const double value);

signals:
    void sendCommand(char* command);
    void sendByteCommand(QByteArray buffer);
    void sendToPrintScheduler(char bedChar,int state);

public slots:
    void receiveFromBedSerialPort(char bedChar);
    void receiveFromPrintScheduler(char bedChar,int receive);
    void handleTimeout();
    void getBedState(char bedChar,int* statePtr);

    void receiveFromPrintSchedulerSendCommand(char bedChar,QString command);

public:
    char bedChar;
    const double maxHeight = 97;//100//102
    double LayerHeight = 0.1;
    int ZHopHeight = 10;
    int curingTime = 2000;
    int bedCuringTime = 15000;
    int accelSpeed = 10;
    int decelSpeed = 20;
    int maxSpeed = 150;
    int minSpeed = 20;
    int bedState = PRINT_MOVE_NULL;
    int printingState = 0;
    double currentPosition = 0.0;
    double pauseMoveMilli = 0.0;

    QTimer m_timer;
    BedSerialport* bedSerialPort = nullptr;
    QMutex bedControlLock;
    //int motor_accel;
    //int motor_deccel;

private:
};

#endif // BEDCONTROL_H
