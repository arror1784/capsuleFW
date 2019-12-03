#include "logger.h"

Logger* logger = new Logger("log.txt");

Logger::Logger(QString fileName, QPlainTextEdit *editor) {
    //logging
    m_editor = editor;
    m_showDate = true;
    if (!fileName.isEmpty()) {
        file = new QFile;
        file->setFileName(fileName);
        file->open(QIODevice::Append | QIODevice::Text);
    }
}

void Logger::write(const QString &value) {
    log_lock.lock();
    QString text = value + "\n";
    if (m_showDate)
        text = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss zzz ") + text;
    QTextStream out(file);
     out.setCodec("UTF-8");
    if (file != 0) {
        out << text;
    }
    if (m_editor != 0)
        m_editor->appendPlainText(text);
    log_lock.unlock();
}

void Logger::setShowDateTime(bool value) {
    m_showDate = value;
}

Logger::~Logger() {
    if (file != 0)
        file->close();
}

