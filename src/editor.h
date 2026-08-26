#pragma once

#include "scenemanager.h"

#ifdef DEBUG
#include <rlImGui.h>
#include <imgui.h>
#endif

class Editor
{
private:
    SceneManager &sceneManger;
    std::string m_selectedSceneName;

public:
    Editor(SceneManager &sceneManager) : sceneManger(sceneManager) {};
#ifdef DEBUG
    void draw()
    {
        ImGui::Begin("Inspetor");

        if (sceneManger.hasActiveScene())
            ImGui::Text("Scene: %s", sceneManger.getActiveSceneName().c_str());
        else
            ImGui::TextColored({1, 0, 0, 1}, "No scene loaded.");

        ImGui::Separator();

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

        ImGui::Spacing();
        
        ImGui::BeginDisabled(m_selectedSceneName.empty());
        if (ImGui::Button("Trocar Cena"))
        {
            if (!m_selectedSceneName.empty())
                sceneManger.changeScene(m_selectedSceneName);
        }
        ImGui::EndDisabled();

        ImGui::End();
    }
#endif
};
