#pragma once

#include <raylib.h>
#include <entt/entt.hpp>

namespace Engine
{
    struct TagComponent
    {
        std::string name = "Entity";
    };

    struct BoxColliderComponent
    {
        Vector2 offset = {0, 0};
        Vector2 size = {0, 0};
    };

    struct BodyComponent
    {
        float mass = {1};
        float gravity = {0};
        Vector2 velocity = {0, 0};
        bool isStatic = false;
    };
    
    struct SpriteComponent
    {
        Texture2D *texture = nullptr;
        Rectangle sourceRect = {0};
        Color color;
    };

    struct SpriteAnimationComponent
    {
        int fps = 0;
        int curFrame = 0;
        int maxFrames = 0;
        float frameTimer;
    };

    struct RectangleComponent
    {
        Vector2 size = {1, 1};
        Color color;
    };

    struct TransformComponent
    {
        Vector2 position = {0, 0};
        float rotation = 0;
        Vector2 scale = {1, 1};
    };
};