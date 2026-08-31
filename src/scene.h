#pragma once
#include <raylib.h>
#include <entt/entt.hpp>
#include "entity.h"

namespace Engine
{
    class SceneManager;

    class Scene
    {
    public:
        const std::string name;
        Scene(const std::string sceneName) : name(sceneName) {};

        virtual ~Scene() = default;

        virtual void start() = 0;
        virtual void stop() = 0;

        virtual void update(SceneManager &sm, float deltaTime) = 0;
        virtual void draw() = 0;

    private:
        friend class Entity;
        friend class SceneManager;
        friend class Editor;

        entt::registry registry;

    protected:
        Entity createEntity()
        {
            Entity e = {registry.create(), this};
            e.addComponent<Transform>();
            return e;
        };
        Color backgroundColor = BLUE;
    };
};