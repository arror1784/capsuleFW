#include "hdmicontrol.h"

#include <QProcess>

void HDMIControl::hdmiRefresh()
{
    QProcess::execute("vcgencmd display_power 0");
    QProcess::execute("vcgencmd display_power 1");
}
