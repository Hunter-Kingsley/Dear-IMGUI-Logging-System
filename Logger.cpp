#include "Logger.h"
#include "imgui/imgui.h"
#include <iostream>
#include <chrono>

Logger* Logger::s_instance = nullptr;

void Logger::RenderLogger() {

    ImGui::Begin("Game Log");

    if(ImGui::Button("Options")) {
        // TODO
    }
    ImGui::SameLine();

    if(ImGui::Button("Clear")) {
        log_bank.clear();
    }
    ImGui::SameLine();

    if(ImGui::Button("Test Info")) {
        log_info temp_log;
        
        temp_log.Time = Logger::GetTime();
        temp_log.isGameEvent = false;
        temp_log.Log_Level = LOG_LEVEL::INFO;
        temp_log.Message = "This is a test info message";

        log_bank.push_back(temp_log);
    }
    ImGui::SameLine();

    if(ImGui::Button("Test Warning")) {
        log_info temp_log;
        
        temp_log.Time = Logger::GetTime();
        temp_log.isGameEvent = false;
        temp_log.Log_Level = LOG_LEVEL::WARNING;
        temp_log.Message = "This is a test warning message";

        log_bank.push_back(temp_log);
    }
    ImGui::SameLine();

    if(ImGui::Button("Test Error")) {
        log_info temp_log;
        
        temp_log.Time = Logger::GetTime();
        temp_log.isGameEvent = false;
        temp_log.Log_Level = LOG_LEVEL::ERROR;
        temp_log.Message = "This is a test error message";

        log_bank.push_back(temp_log);
    }

    ImGui::Separator();

    ImGui::BeginChild("Log Area");
    PublishLogs();
    ImGui::EndChild();

    ImGui::End();
}

void Logger::LogInfo(std::string S) {

    log_info temp_log;
        
    temp_log.Time = Logger::GetTime();
    temp_log.isGameEvent = false;
    temp_log.Log_Level = LOG_LEVEL::INFO;
    temp_log.Message = S;

    log_bank.push_back(temp_log);
}

void Logger::LogGameEvent(std::string S) {
        
    log_info temp_log;
        
    temp_log.Time = Logger::GetTime();
    temp_log.isGameEvent = true;
    temp_log.Log_Level = LOG_LEVEL::INFO;
    temp_log.Message = S;

    log_bank.push_back(temp_log);
}

void Logger::LogWarning(std::string S) {
        
    log_info temp_log;
        
    temp_log.Time = Logger::GetTime();
    temp_log.isGameEvent = false;
    temp_log.Log_Level = LOG_LEVEL::WARNING;
    temp_log.Message = S;

    log_bank.push_back(temp_log);
}

void Logger::LogGameWarning(std::string S) {
        
    log_info temp_log;
        
    temp_log.Time = Logger::GetTime();
    temp_log.isGameEvent = true;
    temp_log.Log_Level = LOG_LEVEL::WARNING;
    temp_log.Message = S;

    log_bank.push_back(temp_log);
}

void Logger::LogError(std::string S) {
    
    log_info temp_log;
        
    temp_log.Time = Logger::GetTime();
    temp_log.isGameEvent = false;
    temp_log.Log_Level = LOG_LEVEL::ERROR;
    temp_log.Message = S;

    log_bank.push_back(temp_log);
}

void Logger::LogGameError(std::string S) {
    
    log_info temp_log;
        
    temp_log.Time = Logger::GetTime();
    temp_log.isGameEvent = true;
    temp_log.Log_Level = LOG_LEVEL::ERROR;
    temp_log.Message = S;

    log_bank.push_back(temp_log);
}

std::string Logger::GetTime() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    std::time_t t = system_clock::to_time_t(now);

    std::tm buf;
#if defined(_WIN32)
    localtime_s(&buf, &t);
#else
    localtime_r(&t, &buf);
#endif

    std::ostringstream oss;
    oss << std::put_time(&buf, "%H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

void Logger::PublishLogs() {

    for (const log_info& log_to_send : log_bank) {
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
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            break;
    
        case LOG_LEVEL::WARNING:
            log_string += "WARN";
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.65f, 0.0f, 1.0f));
            break;
    
        case LOG_LEVEL::ERROR:
            log_string += "ERROR";
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
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
        log_string += '\n';
    
        // add it to the log string
        ImGui::Text(log_string.c_str());
        ImGui::PopStyleColor();
    }
}