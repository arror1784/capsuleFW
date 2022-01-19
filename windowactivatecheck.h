#ifndef WINDOWACTIVATECHECK_H
#define WINDOWACTIVATECHECK_H

#include <QObject>

class WindowActivateCheck : public QObject
{
    Q_OBJECT
public:
    explicit WindowActivateCheck(QObject *parent = nullptr);

signals:
    void activeWindow();

public slots:
    void activePrintWindow(){ emit activeWindow(); }

};

#endif // WINDOWACTIVATECHECK_H
