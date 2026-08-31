#pragma once
#include <format>
#include <deque>
#include <imgui.h>

#ifndef _WIN32
#define printf_s printf
#endif

namespace Engine
{
    class Logger
    {
    private:
        static const int maxlogs = 10;
        inline static std::deque<std::string> buffer;
        inline static bool autoscrool = true;

    public:
        template <typename... Args>
        inline static void Log(std::format_string<Args...> fmt, Args &&...args)
        {
            std::string message = std::format(fmt, std::forward<Args>(args)...);
            buffer.push_back(message);
            printf_s("%s\n", message.c_str());

            if (buffer.size() > maxlogs)
                buffer.pop_front();
        };

        template <typename... Args>
        inline static void Info(std::format_string<Args...> fmt, Args &&...args)
        {
            std::string message = std::format(fmt, std::forward<Args>(args)...);
            Log("[INFO] {}", message);
        };

        template <typename... Args>
        inline static void Warning(std::format_string<Args...> fmt, Args &&...args)
        {
            std::string message = std::format(fmt, std::forward<Args>(args)...);
            Log("[WARNING] {}", message);
        };

        template <typename... Args>
        inline static void Error(std::format_string<Args...> fmt, Args &&...args)
        {
            std::string message = std::format(fmt, std::forward<Args>(args)...);
            Log("[ERROR] {}", message);
        };

        inline static void Clear()
        {
            buffer.clear();
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

            for (const auto &log : buffer)
            {
                bool color = false;

                if (log.contains("[INFO]"))
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(166.f / 255, 255.f / 255, 216.f / 255, 1.0f));
                    color = true;
                }

                if (log.contains("[WARNING]"))
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
                    color = true;
                }

                if (log.contains("[ERROR]"))
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                    color = true;
                }

                ImGui::TextUnformatted(log.c_str());

                if (color)
                    ImGui::PopStyleColor();
            }

            if (autoscrool && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);

            ImGui::EndChild();
            ImGui::End();
        };
    };
};