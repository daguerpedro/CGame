#pragma once

#include "scenemanager.h"

#ifdef DEBUG
#include <rlImGui.h>
#include <imgui.h>
#endif

class Editor
{
private:
    SceneManager &m_sceneManager;

public:
    Editor(SceneManager &sceneManager) : m_sceneManager(sceneManager) {};
#ifdef DEBUG
    void draw()
    {
        ImGui::Begin("Inspetor");
        ImGui::End();
    }
#endif
};

