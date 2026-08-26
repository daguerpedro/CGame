#pragma once
#include <raylib.h>

class Scene
{
public:
    Scene() { };
    ~Scene() = default;

    virtual void start() = 0;
    virtual void update(float dt) = 0;

    Color backgroundColor = BLUE;
};