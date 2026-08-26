#pragma once
#include <raylib.h>

class SceneManager;

class Scene
{
public:
    const std::string name;
    Scene(const std::string sceneName) : name(sceneName) { };

    virtual ~Scene() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void update(SceneManager &sm, float deltaTime) = 0;
    virtual void draw() = 0;

    Color backgroundColor = BLUE;
};