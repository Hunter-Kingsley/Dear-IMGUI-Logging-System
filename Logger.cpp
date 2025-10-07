#include "Logger.h"
#include "imgui/imgui.h"

void Logger::RenderLogger() {
    printf("I AM STRAIGHT UP RENDERING IT");

    ImGui::Begin("Game Log");

    if(ImGui::Button("Options")) {
        // TODO
    }

    if(ImGui::Button("Clear")) {
        // TODO
    }

    if(ImGui::Button("Test Info")) {
        log_info temp_log;
        
        temp_log.Time = Logger::GetTime();
        temp_log.isGameEvent = false;
        temp_log.Log_Level = LOG_LEVEL::INFO;
        temp_log.Message = "This is a test info message";

        Logger::SendLog(temp_log);
    }

    if(ImGui::Button("Test Warning")) {
        // TODO
    }

    if(ImGui::Button("Test Error")) {
        // TODO
    }

    ImGui::End();
}

std::string Logger::GetTime() {
    time_t my_time = time(NULL);

    return ctime(&my_time);
}

void Logger::SendLog(log_info log_to_send) {
    std::string log_string;

    // add time
    log_string += "[";
    log_string += log_to_send.Time;
    log_string += "] ";

    // add log level
    log_string += "[";
    switch (log_to_send.Log_Level)
    {
    case LOG_LEVEL::INFO:
        log_string += "INFO";
        break;

    case LOG_LEVEL::WARNING:
        log_string += "WARN";
        break;

    case LOG_LEVEL::ERROR:
        log_string += "ERROR";
        break;
    
    default:
        break;
    }
    log_string += "] ";

    // add if its a game log
    if (log_to_send.isGameEvent) {
        log_string += "[";
        log_string += "GAME";
        log_string += "] ";
    }

    // add log message
    log_string += log_to_send.Message;

    // send it with imgui
    ImGui::LogText(log_string.c_str());
}