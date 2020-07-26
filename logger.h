#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QPlainTextEdit>
#include <QDateTime>
#include <QTextStream>
#include <QMutex>

class Logger : QObject
{
    Q_OBJECT
private:
    Logger();
    Logger(QString fileName);
    Logger(const Logger& other);
    ~Logger();

    static Logger* _ins;

    QFile *file;
    bool m_showDate;
    bool _logging = true;

public:
    static Logger* GetInstance()
    {
        if (_ins == nullptr) {
            _ins = new Logger("log.txt");
            atexit(release_instance);
        }
        return _ins;
    }
    static void release_instance() {
        if(_ins){
            delete _ins;
            _ins = nullptr;
        }
    }
    void setShowDateTime(bool value);
    void write(const QString &value);
};

#endif // LOGGER_H
