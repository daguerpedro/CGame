#pragma once
#include <raylib.h>
#include "editor.h"
#include "scene.h"
#include "scenemanager.h"
#include "renderer.h"
#include <cassert>

namespace Engine
{   
    
    class App
    {
    protected:
    private:
        Editor m_editor;

        Renderer m_renderer;
        RenderTexture2D gameViewTexture;

        void setupRaylib(const char *title, int w, int h);
        void setupImGui(int w, int h);
        void cleanUp();
    public:
        App() : m_editor(sceneManager) {};

        SceneManager sceneManager;
        
        void init(const char *title, int w, int h);
        void start();

        //TEMP?
        std::function<void()> onStart;
    };
};
