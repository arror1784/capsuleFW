#include "factoryreset.h"

#include <QProcess>

FactoryReset::FactoryReset(QObject *parent) : QObject(parent)
{

}

void FactoryReset::reset()
{
    QProcess::execute("bash -c \"echo rasp | sudo -S /boot/factory_reset --reset > /home/pi/out 2>&1\"");
}
