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

namespace Engine
{

    class Editor
    {
    public:
#ifndef DEBUG
        Editor(SceneManager &sceneManager) {};

#endif
#ifdef DEBUG
        Editor(SceneManager &sceneManager) : sceneManager(sceneManager) {};
        void draw();

    private:
        SceneManager &sceneManager;
        std::string m_selectedSceneName;

        void inspectorWindow();

        void activeScene();
        void sceneList();
        void entityList();
        void changeScene();

        float values[60] = {0};
        int values_offset = 0;
        double refresh_time = 0.0;

        float max = 0.000000f;

        void statsWindow();
#endif
    };
};