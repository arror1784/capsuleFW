#include "kinetimecalc.h"

#include <QDebug>

double KineTimeCalc::calcTRMoveTime(float maxSpeed, float minSpeed, float accelSpeed, float decelSpeed, float distance)
{
    double A = (accelSpeed + (3 * pow(accelSpeed,2)) / - decelSpeed) * 0.5 ;

    qDebug() << "A : " << A;

    double B = minSpeed + ((accelSpeed / -decelSpeed) * minSpeed);

    qDebug() << "B : " << B;

    double C = -distance;

    qDebug() << "C : " << C;

    double timeA = (-B + sqrt(pow(B,2) - (4*A*C))) / (2*A);

    qDebug() << "timeA : " << timeA;

    double timeD = (accelSpeed * timeA) / -decelSpeed;

    qDebug() << "timeD : " << timeD;

    return timeA + timeD;
}
