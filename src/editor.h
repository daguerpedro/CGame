#pragma once

#include "scenemanager.h"
#include "logger.h"

#ifdef DEBUG
#include <rlImGui.h>
#include <imgui.h>
#endif

class Editor
{
public:
    Editor(SceneManager &sceneManager) : sceneManger(sceneManager) {};
#ifdef DEBUG
    void draw()
    {
        if (ImGui::Begin("Inspetor"))
        {
            activeScene();
            sceneList();
            changeScene();
            ImGui::End();
        }

        Logger::Draw();
    }

private:
    SceneManager &sceneManger;
    std::string m_selectedSceneName;

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
#endif
};
