#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, Logger::LOG_LEVEL> Logger::log_level = std::unordered_map<std::string, Logger::LOG_LEVEL>();
std::unordered_map<std::string, std::string> Logger::logger_appender_link = std::unordered_map<std::string, std::string>();
std::unordered_map<std::string, AppenderInfo> Logger::message_colors = std::unordered_map<std::string, AppenderInfo>();

void Logger::setLogConfigFile(std::string filePath)
{
    readConfigFile(filePath);
}

void Logger::addAppender(std::string logger_name, std::string appender_name)
{
    Logger::logger_appender_link[logger_name] = appender_name;
}

void Logger::addLogger(std::string logger_name, std::string log_level)
{
    std::cout << "LOGLEVEL READ: " << log_level << std::endl;
    if (log_level == "INFO")
    {
        Logger::log_level[logger_name] = LOG_LEVEL::INFO;
    }
    else if (log_level == "DEBUG")
    {
        Logger::log_level[logger_name] = LOG_LEVEL::DEBUG;
    }
    else if (log_level == "TRACE")
    {
        Logger::log_level[logger_name] = LOG_LEVEL::TRACE;
    }
    else if (log_level == "WARN")
    {
        Logger::log_level[logger_name] = LOG_LEVEL::WARN;
    }
    else if (log_level == "ERROR")
    {
        Logger::log_level[logger_name] = LOG_LEVEL::ERROR;
    }   
}

void Logger::readConfigFile(std::string filePath)
{
    std::ifstream config_file = std::ifstream(filePath);
    for (std::string line; std::getline(config_file, line);)
    {
        if (line.size() > 6 && line.substr(0, 6) == "LOGGER") //? Line that defines the visibility of a logger
        {
            std::string logger = line.substr(7);
            std::string logger_name = logger.substr(0, logger.find('='));


            std::istringstream config(logger.substr(logger_name.size() + 1));
            std::string config_info;
            std::getline(config, config_info, ',');
            addLogger(logger_name, config_info);
            std::getline(config, config_info, ',');
            addAppender(logger_name, config_info);
        }
        else if (!line.empty())
        {
            std::string appender_name = line.substr(0, line.find('.'));
            std::cout << "name of the appender to add: " << appender_name << std::endl;
            if (Logger::message_colors.count(appender_name) == 0)
            {
                Logger::message_colors[appender_name] = AppenderInfo();
                std::cout << "Created the AppenderInfo object for appender: " << appender_name << std::endl;;
            }
            
            std::string appender_info_tag = line.substr(appender_name.size() + 1, line.find('=') - appender_name.size() - 1);
            std::string appender_info_value = line.substr(line.find('=') + 1);

            std::cout << "Appender info tag is: " << appender_info_tag << std::endl;
            std::cout << "Appender info value is: " << appender_info_value << std::endl;
            std::cout << "====" << line.find('=') << " raw line is[" << line << "] size: " << line.size() << std::endl << std::endl;

            if (appender_info_tag == "AppenderType")
                Logger::message_colors[appender_name].fileDescriptor = 1;
            else if (appender_info_tag == "info_color")
                Logger::message_colors[appender_name].info_color = appender_info_value;
            else if (appender_info_tag == "debug_color")
                Logger::message_colors[appender_name].debug_color = appender_info_value;
            else if (appender_info_tag == "trace_color")
                Logger::message_colors[appender_name].trace_color = appender_info_value;
            else if (appender_info_tag == "warn_color")
                Logger::message_colors[appender_name].warn_color = appender_info_value;
            else if (appender_info_tag == "error_color")
                Logger::message_colors[appender_name].error_color = appender_info_value;
            else if (appender_info_tag == "flush")
                if (appender_info_value == "true")
                    Logger::message_colors[appender_name].flush = true;
                else
                    Logger::message_colors[appender_name].flush = false;
        }
    }
}

std::string Logger::getDateAndTime()
{
    auto time = std::chrono::system_clock::now();
    std::time_t formated_time = std::chrono::system_clock::to_time_t(time);
    std::string time_to_print = std::ctime(&formated_time);
    time_to_print.pop_back();
    return time_to_print;
}

void Logger::log_info(std::string appender, std::string message)
{
    std::cout << "tttttttttt" << Logger::log_level[appender] << std::endl;
    if (Logger::log_level[appender] && Logger::log_level[appender] >= LOG_LEVEL::INFO)
    {
        std::cout << getDateAndTime() << ": " << appender << "-" << message << std::endl;
    }
}

void Logger::log_debug(std::string appender, std::string message)
{
    if (Logger::log_level[appender] && Logger::log_level[appender] >= LOG_LEVEL::DEBUG)
    {
        std::cout << getDateAndTime() << ": " << appender << "-" << message << std::endl;
    }
}

void Logger::log_trace(std::string appender, std::string message)
{
    if (Logger::log_level[appender] && Logger::log_level[appender] >= LOG_LEVEL::TRACE)
    {
        std::cout << getDateAndTime() << ": " << appender << "-" << message << std::endl;
    }
}

void Logger::log_warn(std::string appender, std::string message)
{
    if (Logger::log_level[appender] && Logger::log_level[appender] >= LOG_LEVEL::WARN)
    {
        std::cout << getDateAndTime() << ": " << appender << "-" << message << std::endl;
    }
}

void Logger::log_error(std::string appender, std::string message)
{
    if (Logger::log_level[appender] && Logger::log_level[appender] >= LOG_LEVEL::ERROR)
    {
        std::cout << getDateAndTime() << ": " << appender << "-" << message << std::endl;
    }
}
