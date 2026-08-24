#include <iostream>
#include <raylib.h>
#include "tower.h"
#include "wavemanager.h"
#include "text.h"

int WIDTH;
int HEIGHT;

int main(int, char **)
{
    WIDTH = 800;
    HEIGHT = 600;

    InitWindow(WIDTH, HEIGHT, "Jogo");

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    float dt = 0;

    Text tWave("Wave 0", {15, 15}, 15, WHITE);
    Text tEnemies("0 Enemies", {15, 35}, 15, WHITE);

    Tower tower;
    tower.setSize(20.f);
    tower.setPosition({WIDTH/2.f - 10, HEIGHT/2.f - 10});
    tower.setColor(BLUE);
    
    WaveManager waveManager;
    
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(Color{47, 50, 54});

        dt = GetFrameTime();

        waveManager.update(dt);

        tower.update(dt);
        tower.draw();

        tWave.text = std::format("Wave {}", waveManager.getWave());
        tWave.draw();

        tEnemies.text = std::format("{} Enemies", waveManager.getEnemies());
        tEnemies.draw();

        if(IsKeyPressed(KEY_RIGHT))
            waveManager.startNextWave();
        if(IsKeyPressed(KEY_LEFT))
            waveManager.reset();
        
        EndDrawing();
    }

    CloseWindow();
}