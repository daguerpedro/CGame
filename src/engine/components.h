#pragma once

#include <raylib.h>
#include <entt/entt.hpp>

namespace Engine
{
    struct TAG
    {
        std::string name = "Entity";
    };

    struct BoxCollider
    {
        Vector2 offset = {0};
        Vector2 size = {0};
    };

    struct Body
    {
        float mass = {1};
        float gravity = {0};
        Vector2 velocity = {0};
        bool isStatic = false;
    };
    
    struct Sprite
    {
        Texture2D *texture = nullptr;
        Rectangle sourceRect = {0};
        Color color;
    };

    struct SpriteAnimation
    {
        int fps = 0;
        int curFrame = 0;
        int maxFrames = 0;
        float frameTimer;
    };

    struct Transform
    {
        Vector2 position = {0};
        float rotation = 0;
        Vector2 scale = {1};
    };
};