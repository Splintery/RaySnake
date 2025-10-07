#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <sstream>

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
    if (log_level == "INFO") Logger::log_level[logger_name] = LOG_LEVEL::INFO;
    else if (log_level == "DEBUG") Logger::log_level[logger_name] = LOG_LEVEL::DEBUG;
    else if (log_level == "TRACE") Logger::log_level[logger_name] = LOG_LEVEL::TRACE;
    else if (log_level == "WARN") Logger::log_level[logger_name] = LOG_LEVEL::WARN;
    else if (log_level == "ERROR") Logger::log_level[logger_name] = LOG_LEVEL::ERROR;   
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


            std::istringstream config(logger.substr(logger_name.size()));
            std::string config_info;
            std::getline(config, config_info, ',');
            addLogger(logger_name, config_info);
            std::getline(config, config_info, ',');
            addAppender(logger_name, config_info);
        }
        else if (!line.empty())
        {
            std::string appender_name = line.substr(0, line.find('.'));
            if (Logger::message_colors.count(appender_name) == 0)
            {
                Logger::message_colors[appender_name] = AppenderInfo();
            }
            else
            {
                std::string appender_info_tag = line.substr(line.find('.') + 1, line.find('='));
                std::string appender_info_value = line.substr(line.find('='));
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
}

std::string Logger::getDateAndTime()
{
    auto time = std::chrono::system_clock::now();
    std::time_t formated_time = std::chrono::system_clock::to_time_t(time);

    return std::ctime(&formated_time);
}

void Logger::log_info(std::string appender, std::string message)
{
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
