#include "app.h"

#ifdef DEBUG
#include <fstream>
#define EDITOR_CFG "editor.cfg"
#endif

void App::init(const char *title, int w, int h)
{
    setupRaylib(title, w, h);
    setupImGui(w, h);
};

void App::loop()
{
    while (WindowShouldClose() == false)
    {
        float deltaTime = GetFrameTime();

#ifndef DEBUG
        BeginDrawing();
            ClearBackground(DARKGRAY); // TODO: CLEAR WITH SCENE BG
            m_sceneManager.draw();
        EndDrawing();
#endif

#ifdef DEBUG
        BeginTextureMode(gameViewTexture);
            ClearBackground(DARKGRAY); // TODO: CLEAR WITH SCENE BG
            m_sceneManager.draw();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            rlImGuiBegin();

                ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
                ImGui::Begin("Viewport");
                ImGui::PopStyleVar();
                    ImVec2 viewSize = ImGui::GetContentRegionAvail();
                    if (viewSize.x > 0 && viewSize.y > 0 && (viewSize.x != gameViewTexture.texture.width || viewSize.y != gameViewTexture.texture.height)) 
                    { 
                        UnloadRenderTexture(gameViewTexture);
                        gameViewTexture = LoadRenderTexture((int)viewSize.x, (int)viewSize.y);
                    }
                    rlImGuiImageRenderTexture(&gameViewTexture);
                ImGui::End();

                m_editor.draw();

            rlImGuiEnd();
        EndDrawing();
#endif
    }

    cleanUp();
};

void App::setupRaylib(const char *title, int w, int h)
{
    int width = w;
    int height = h;
    bool maximized = false;

#ifdef DEBUG
    std::ifstream configFile(EDITOR_CFG);
    if (configFile.is_open()) 
    {
        configFile >> width >> height >> maximized;
        configFile.close();
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
#endif

    InitWindow(width, height, title);

    if(maximized)
        MaximizeWindow();

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
}

void App::setupImGui(int w, int h)
{
#ifdef DEBUG
    rlImGuiSetup(true);
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    gameViewTexture = LoadRenderTexture(w, h);
#endif
}

void App::cleanUp()
{
#ifdef DEBUG
    UnloadRenderTexture(gameViewTexture);
    rlImGuiShutdown();
    
    std::ofstream configFile(EDITOR_CFG);
    if (configFile.is_open()) {
        configFile << GetScreenWidth() << " " << GetScreenHeight() << " " << IsWindowMaximized();
        configFile.close();
    }
#endif

    CloseWindow();
}
