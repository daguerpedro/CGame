#include <iostream>
#include "app.h"

class Test : public Scene
{
public:
    Test() : Scene("Test")
    {

    }

    void start() override
    {
        backgroundColor = {155, 155, 155};
    }

    void stop() override
    {

    }

    void update(SceneManager &sm, float deltaTime) override
    {

    }

    void draw() override
    {

    }
};

class Menu : public Scene
{
public:
    Menu() : Scene("Menu")
    {
        
    }

    void start() override
    {
        backgroundColor = BLACK;
    }

    void stop() override
    {

    }

    void update(SceneManager &sm, float deltaTime) override
    {

    }

    void draw() override
    {

    }
};

int main(int, char **)
{
    App app;
    app.init("Desenvolvimento", 800, 600);
    
    auto& sm = app.sceneManager;
    sm.registerScene<Test>("Test");
    sm.registerScene<Menu>("Menu");    
    
    app.loop();

    return 0;
}