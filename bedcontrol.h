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
    BedControl(char bedChar,BedSerialport* bedSerialPor1t);
    virtual void run();

    void (BedControl::*current_function)() = nullptr;

    void setAccleSpeed(int val,int mode);
    void setDecelSpeed(int val,int mode);

    void setUpAccleSpeed(int val);
    void setUpDecelSpeed(int val);
    void setDownAccleSpeed(int val);
    void setDownDecelSpeed(int val);

    void setMaxSpeed(int val);
    void setMinSpeed(int val);

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

signals:
    void sendCommand(QString command);
    void sendByteCommand(QByteArray buffer);
    void sendToPrintScheduler(char bedChar,int state);

public slots:
    void receiveFromBedSerialPort(char bedChar);
    void receiveFromPrintScheduler(char bedChar,int receive);
    void handleTimeout();
    void getBedState(char bedChar,int* statePtr);

public:
    char bedChar;
    const int defaultHeight = 102700; //100//102//97600//102700//102400
    int maxHeight = 0;
    int LayerHeight = 100;
    int ZHopHeight = 10000;
    int curingTime = 2000;
    int bedCuringTime = 15000;
    int bedState = PRINT_MOVE_NULL;
    int printingState = 0;

    int maxSpeed = 150;
    int minSpeed = 20;

    int accelSpeed = 10;
    int decelSpeed = 20;
    int upAccelSpeed = 10;
    int upDecelSpeed = 10;
    int downAccelSpeed = 10;
    int downDecelSpeed = 10;

    int firstAccelSpeed = 10;
    int firstDecelSpeed = 20;
    int firstMaxSpeed = 150;
    int firstMinSpeed = 20;


    int layerDelay = 1000;

//    double currentPosition = 0.0;
//    double pauseMoveMilli = 0.0;

    QTimer m_timer;
    BedSerialport* bedSerialPort = nullptr;
    QMutex bedControlLock;
    //int motor_accel;
    //int motor_deccel;

private:
};

#endif // BEDCONTROL_H
