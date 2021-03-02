#ifndef FACTORYRESET_H
#define FACTORYRESET_H

#include <QObject>
#include "Singleton.h"

class FactoryReset : public QObject, public Hix::Common::Singleton<FactoryReset>
{
    Q_OBJECT
public:
    explicit FactoryReset(QObject *parent = nullptr);

signals:

public slots:
    void reset();
};

#endif // FACTORYRESET_H
