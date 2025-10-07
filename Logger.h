#pragma once

#include <string>
#include <time.h>

enum class LOG_LEVEL {
    INFO,
    WARNING,
    ERROR
};

struct log_info
{
    std::string Time;
    LOG_LEVEL Log_Level;
    bool isGameEvent;
    std::string Message;
};


class Logger {
    public:
        static Logger& GetInstance()
        {
            static Logger Logger_Instance;
            return Logger_Instance;
        };
        void RenderLogger();
        
        void LogInfo();
        void LogGameEvent();
        void LogWarning();
        void LogError();
    private:
        Logger() {}
        std::string GetTime();
        void SendLog(log_info L);
};