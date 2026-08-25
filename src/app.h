#pragma once
#include <raylib.h>
#include "editor.h"
#include "scene.h"
#include "scenemanager.h"

class App
{
protected:
private:
    SceneManager m_sceneManager;
    Editor m_editor;
    RenderTexture2D gameViewTexture;

    void setupRaylib(const char *title, int w, int h);
    void setupImGui(int w, int h);
    void cleanUp();
    
public:
    App() : m_editor(m_sceneManager)
    {

    };

    void init(const char *title, int w, int h);
    void loop();
};