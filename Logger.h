#pragma once
#include <string>

enum class LOG_TYPE {
    INFO,
    WARNING,
    ERROR
};

struct log
{
    std::string Time;
    LOG_TYPE Log_Level;
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
};