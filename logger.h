#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QPlainTextEdit>
#include <QDateTime>
#include <QTextStream>
#include <QMutex>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QString fileName, QPlainTextEdit *editor = 0);
    ~Logger();
    void setShowDateTime(bool value);

private:
    QFile *file;
    QPlainTextEdit *m_editor;
    bool m_showDate;
    QMutex log_lock;

signals:

public slots:
    void write(const QString &value);

};
extern Logger* logger;
#endif // LOGGER_H
