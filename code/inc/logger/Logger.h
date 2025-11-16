#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <unordered_map>

/*
\033[X;X;XmMymessage\033[0m
         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47

Additionally, you can use these:

reset             0  (everything back to normal)
bold/bright       1  (often a brighter shade of the same colour)
underline         4
inverse           7  (swap foreground and background colours)
bold/bright off  21
underline off    24
inverse off      27
*/
#define LOG_INFO(name, msg) Logger::log_if_level(Logger::LOG_LEVEL::INFO, name, msg)
#define LOG_DEBUG(name, msg) Logger::log_if_level(Logger::LOG_LEVEL::DEBUG, name, msg)
#define LOG_TRACE(name, msg) Logger::log_if_level(Logger::LOG_LEVEL::TRACE, name, msg)
#define LOG_WARN(name, msg) Logger::log_if_exist(name, msg)
#define LOG_ERROR(name, msg) Logger::log_if_exist(name, msg)

struct Appender
{
    int fileDescriptor;
    std::string appender_color[5]; //* 0 is INFO, 1 is DEBUG, 2 is TRACE, 3 is WARN anc 4 is ERROR
    bool flush;
};

class Logger
{
public:
    enum LOG_LEVEL{
        INFO = 0,
        DEBUG = 1,
        TRACE = 2,
        WARN = 3,
        ERROR = 4
    };
    Logger() = delete;
    Logger(Logger &) = delete;
    virtual ~Logger() = delete;
    static void setLogConfigFile(std::string);
private:
    static std::unordered_map<std::string, LOG_LEVEL> log_level;
    static std::unordered_map<std::string, std::string> logger_appender_link;
    static std::unordered_map<std::string, Appender> message_colors;
    
    static void addAppender(std::string, std::string);
    static void addLogger(std::string, std::string);
    static void readConfigFile(std::string);
    static void readAppenderSettings(std::string);
    static void readLoggerSettings(std::string);
    static std::string getDateAndTime();
public:
    static void log_colored(
        std::string color, 
        std::string date, 
        std::string logger, 
        std::string msg
    );
    static void log_to_file(
        int fd, 
        std::string date, 
        std::string logger, 
        std::string msg
    );
    static void log_if_level(LOG_LEVEL, std::string, std::string);
    static void log_if_exist(std::string, std::string);
};

#endif