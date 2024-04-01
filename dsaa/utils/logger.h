#ifndef LOGGER
#define LOGGER

#define LOCALLOGLEVEL INFO

class QString;
class Logger {
public:
    enum LogLevel { NONE, DEBUG, INFO, WARNING, ERR, };
    
private:
    static LogLevel _level;
    static QString _previous;
    
public:
    static void setLogLevel(LogLevel level);
    static void log(LogLevel level, const QString& message);
    static void debug(const QString& message);
    static void info(const QString& message);
    static void warning(const QString& message);
    static void error(const QString& message);
};

#endif