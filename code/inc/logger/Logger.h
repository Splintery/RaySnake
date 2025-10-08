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
#define LOG_INFO(name, msg) Logger::log_info(name, msg)
#define LOG_DEBUG(name, msg) Logger::log_debug(name, msg)
#define LOG_TRACE(name, msg) Logger::log_trace(name, msg)
#define LOG_WARN(name, msg) Logger::log_warn(name, msg)
#define LOG_ERROR(name, msg) Logger::log_error(name, msg)

struct AppenderInfo
{
    int fileDescriptor;
    std::string info_color;     //* Used with a console appender to help read logs
    std::string debug_color;    //* Used with a console appender to help read logs
    std::string trace_color;    //* Used with a console appender to help read logs
    std::string warn_color;     //* Used with a console appender to help read logs
    std::string error_color;    //* Used with a console appender to help read logs
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
    static std::unordered_map<std::string, AppenderInfo> message_colors;
    
    static void addAppender(std::string, std::string);
    static void addLogger(std::string, std::string);
    static void readConfigFile(std::string);
    static std::string getDateAndTime();
public:
    static void log_info(std::string, std::string);
    static void log_debug(std::string, std::string);
    static void log_trace(std::string, std::string);
    static void log_warn(std::string, std::string);
    static void log_error(std::string, std::string);
};

#endif