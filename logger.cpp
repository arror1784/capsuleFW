#include "logger.h"

Logger* Logger::_ins = nullptr;

Logger::Logger(QString fileName) {
    //logging
    m_showDate = true;
    if (!fileName.isEmpty()) {
        file = new QFile;
        file->setFileName(fileName);
        file->open(QIODevice::Append | QIODevice::Text);
    }
}

void Logger::write(const QString &value) {
    QString text = value + "\n";
    if(!_logging)
        return;
    if (m_showDate)
        text = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss zzz ") + text;
    QTextStream out(file);
    out.setCodec("UTF-8");
    if (file != 0) {
        out << text;
    }
}

void Logger::setShowDateTime(bool value) {
    m_showDate = value;
}

Logger::~Logger() {
    if (file != 0)
        file->close();
}

