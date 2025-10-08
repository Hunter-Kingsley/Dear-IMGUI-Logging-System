#include "Logger.h"
#include "imgui/imgui.h"
#include <iostream>

Logger* Logger::s_instance = nullptr;

void Logger::RenderLogger() {

    ImGui::Begin("Game Log");

    if(ImGui::Button("Options")) {
        // TODO
    }
    ImGui::SameLine();

    if(ImGui::Button("Clear")) {
        // TODO
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
        // TODO
    }
    ImGui::SameLine();

    if(ImGui::Button("Test Error")) {
        // TODO
    }

    ImGui::Separator();

    ImGui::BeginChild("Log Area");
    PublishLogs();
    ImGui::EndChild();

    ImGui::End();
}

std::string Logger::GetTime() {
    time_t my_time = time(NULL);

    return "Time O'Clock";
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