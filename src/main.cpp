#include <iostream>
#include "engine/app.h"

using namespace Engine;

class Menu : public Scene
{
public:
    Menu() : Scene("Menu")
    {
    }

    void start() override
    {
        backgroundColor = YELLOW;
    }

    void stop() override
    {
    }

    void update(SceneManager &sm, float deltaTime) override
    {
        /*auto view = registry.view<Position, Velocity, Renderable>();

        for (auto ent : view)
        {
            auto [pos, vel, ren] = view.get<Position, Velocity, Renderable>(ent);

            pos.x += vel.x * deltaTime;
            pos.y += vel.y * deltaTime;

            if (pos.x < 0)
                vel.x = -vel.x;

            if (pos.x > sm.viewWidth - ren.size.x)
                vel.x = -vel.x;

            if (pos.y < 0)
                vel.y = -vel.y;

            if (pos.y > sm.viewHeight - ren.size.x)
                vel.y = -vel.y;
        }*/
    }

    void draw() override
    {
        /*auto view = registry.view<Renderable, Position>();

        for (auto ent : view)
        {
            auto &ren = view.get<Renderable>(ent);
            auto &pos = view.get<Position>(ent);

            auto w = ren.size.x * ren.scale;
            auto h = ren.size.y * ren.scale;

            Rectangle rec = {
                pos.x,
                pos.y,
                w,
                h};

            DrawRectanglePro(rec, {w / 2.f, h / 2.f}, ren.rotation, ren.color);
        }*/
    }
};

int main(int, char **)
{
    App app;
    app.init("Desenvolvimento", 800, 600);

    auto &sm = app.sceneManager;
    sm.registerScene<Menu>("Menu");
    sm.changeScene("Menu");
    app.loop();

    return 0;
}