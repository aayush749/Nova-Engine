#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <string_view>

enum class Log
{
    INFO, WARNING, ERR
};

/**
 * A singleton Logger class, which can log simple messages to console
 */
class Logger
{
public:

    static void init(Log defaultLogLevel = Log::INFO, bool breakOnError = false)
    {
        s_DefaultLogLevel = Log::INFO;
        s_BreakOnError = breakOnError;
    }

    static void LogInfo(std::string_view msg)
    {
        log(msg, Log::INFO);
    }

    static void LogWarning(std::string_view msg)
    {
        log(msg, Log::WARNING);
    }

    static void LogError(std::string_view msg)
    {
        log(msg, Log::ERR);
    }

    static void log(std::string_view msg, Log level = s_DefaultLogLevel)
    {
        log(msg.data(), level);
    }

    static void log(const char* msg = nullptr, Log level = s_DefaultLogLevel)
    {
        if(msg)
        {
            updateCurrentTime();
            char timeBuf[80];
            tm tmVar;
            localtime_s(&tmVar, &s_currentTime);
            strftime(timeBuf, sizeof(timeBuf), "%X", &tmVar);
            switch (level)
            {
            case Log::INFO:
                std::cerr << "\x1b[32m"<<timeBuf<<' '
                          <<"INFO: "
                          <<msg<<"\x1b[0m"<<std::endl;
                break;
            
            case Log::WARNING:
                std::cerr << "\x1b[33m"<<timeBuf<<' '
                          <<"WARNING: "
                          <<msg<<"\x1b[0m"<<std::endl;
                break;
            
            case Log::ERR:
                std::cerr << "\x1b[1;4;31m"<<timeBuf<<' '
                          <<"ERR: "
                          <<msg<<"\x1b[0m"<<std::endl;
                
                if(s_BreakOnError)
                    __debugbreak();   
                break;

            default:
                break;
            }
        }
    }
private:
    static void updateCurrentTime()
    {
        time(&s_currentTime);
    }

private:
    inline static Log s_DefaultLogLevel = Log::INFO;
    inline static bool s_BreakOnError = false;
    inline static time_t s_currentTime;
};