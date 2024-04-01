#include "logger.h"
#include <QDebug>
#include <QString>

//Set the logger minimum show level.
Logger::LogLevel Logger::_level = Logger::LogLevel::DEBUG;
QString Logger::_previous = "";

void Logger::setLogLevel(LogLevel level) {
    _level = level;
}

void Logger::log(LogLevel level, const QString& message) {
    if (level < _level) return;
    if (message == _previous) return;
    _previous = message;

    switch (level) {
        case DEBUG:
            qDebug() << "DEBUG: " << message.toStdString().c_str();
            break;
        case INFO:
            qDebug() << "INFO: " << message.toStdString().c_str();
            break;
        case WARNING:
            qDebug() << "WARNING: " << message.toStdString().c_str();
            break;
        case ERR:
            qDebug() << "ERROR: " << message.toStdString().c_str();
            break;
    }
}

void Logger::debug(const QString& message) {
    log(DEBUG, message);
}

void Logger::info(const QString& message) {
    log(INFO, message);
}

void Logger::warning(const QString& message) {
    log(WARNING, message);
}

void Logger::error(const QString& message) {
    log(ERR, message);
}
