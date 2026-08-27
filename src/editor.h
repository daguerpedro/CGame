#pragma once

#include "scenemanager.h"
#include "logger.h"

#ifdef DEBUG
#include <rlImGui.h>
#include <imgui.h>
#endif

#include <algorithm>
#include <raylib.h>
#include <cmath>

class Editor
{
public:
    Editor(SceneManager &sceneManager) : sceneManger(sceneManager) {};
#ifdef DEBUG
    void draw()
    {
        sceneWindow();
        statsWindow();

        Logger::Draw();
    }

private:
    SceneManager &sceneManger;
    std::string m_selectedSceneName;

    void sceneWindow()
    {
        if (ImGui::Begin("Inspetor"))
        {
            activeScene();
            sceneList();
            changeScene();
        }
        ImGui::End();
    };

    void activeScene()
    {
        if (sceneManger.hasActiveScene())
            ImGui::Text("Scene: %s", sceneManger.getActiveSceneName().c_str());
        else
            ImGui::TextColored({1, 0, 0, 1}, "No scene loaded.");

        ImGui::Separator();
    };

    void sceneList()
    {
        ImGui::Spacing();
        ImGui::SetNextItemWidth(-1);
        if (ImGui::BeginListBox("##Scene Registry"))
        {
            for (const auto &[sceneName, constructor] : sceneManger.getRegisteredScenes())
            {
                bool is_selected = (m_selectedSceneName == sceneName);
                if (ImGui::Selectable(sceneName.c_str(), is_selected))
                    m_selectedSceneName = sceneName;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
    };

    void changeScene()
    {
        ImGui::BeginDisabled(m_selectedSceneName.empty());
        if (ImGui::Button("Trocar Cena"))
        {
            if (!m_selectedSceneName.empty())
                sceneManger.changeScene(m_selectedSceneName);
        }
        ImGui::EndDisabled();
    };

    float values[60] = {0};
    int values_offset = 0;
    double refresh_time = 0.0;

    float max = 0.000000f;

    void statsWindow()
    {
        // Code by ImGuiDemoTools :D
        if (refresh_time == 0.0)
        {
            refresh_time = ImGui::GetTime();
        }
        
        while (refresh_time < ImGui::GetTime())
        {
            values[values_offset] = GetFrameTime();
            values_offset = (values_offset + 1) % IM_COUNTOF(values);
            refresh_time += 1.0f / 60.0f;
            
            auto actualMax = (*std::max_element(values, values+values_offset));
            if(max < actualMax)
            {
                max = actualMax;
            }
        }

        if (ImGui::Begin("Stats"))
        {
            float average = 0.0f;
            for (int n = 0; n < IM_COUNTOF(values); n++)
                average += values[n];
            average /= (float)IM_COUNTOF(values);
            char overlay[32];

            ImGui::Text("FPS: %1.f (%1.f)", 1.0 / GetFrameTime(), 1.0 / average);
            ImGui::Text("Frame Time: %.4f (ms)", average * 1000);

            ImGui::SetNextItemWidth(-1);
            ImGui::PlotLines("##ftime", values, IM_COUNTOF(values), values_offset, NULL, 0, max, ImVec2(0, 80.0f));
        }
        ImGui::End();
    }
#endif
};
