#include <iostream>
#include <engine.h>

#include "game/scenes/menu.h"

using Engine::App;

int main(int, char **)
{
    App app;
    app.init("CGame - Dev", 800, 600);

    auto &sm = app.sceneManager;
    sm.registerScene<Menu>("Menu");
    
    app.onStart = [&sm]()
    {
        SetTargetFPS(-1);
        sm.changeScene("Menu");
    };

    app.start();

    return 0;
}