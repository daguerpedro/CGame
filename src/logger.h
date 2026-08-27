#pragma once
#include <format>
#include <deque>
#include <imgui.h>

#ifndef _WIN32
#define printf_s printf
#endif

class Logger
{
public:
    static const int maxlogs = 10;
    inline static std::deque<std::string> logs;
    inline static bool autoscrool = true;

    template <typename... Args>
    inline static void Log(std::format_string<Args...> fmt, Args &&...args)
    {
        std::string message = std::format(fmt, std::forward<Args>(args)...);
        logs.push_back(message);
        printf_s("%s\n", message.c_str());

        if (logs.size() > maxlogs)
            logs.pop_front();
    };

    inline static void Clear()
    {
        logs.clear();
    };

    inline static void Draw()
    {
        ImGui::Begin("Console");

        if (ImGui::Button("Limpar"))
            Clear();
        ImGui::SameLine();
        ImGui::Checkbox("Auto-scroll", &autoscrool);
        ImGui::Separator();

        ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        for (const auto &log : logs)        
            ImGui::TextUnformatted(log.c_str());

        if (autoscrool && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())        
            ImGui::SetScrollHereY(1.0f);
        
        ImGui::EndChild();
        ImGui::End();
    };
};