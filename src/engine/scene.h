#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include "entity.h"
#include "components.h"

namespace Engine
{
    class SceneManager;
    
    class Scene
    {
    public:
        const std::string name;
        Scene(const std::string sceneName) : name(sceneName), sceneManager(nullptr) {};

        virtual ~Scene() = default;

        virtual void start() = 0;
        virtual void stop() = 0;

        virtual void update(float deltaTime) = 0;
        entt::registry registry;

    private:
        friend class Entity;
        friend class Renderer;
        friend class SceneManager;
        friend class Editor;


        void bindSceneManager(SceneManager &sm)
        {
            sceneManager = &sm;
        }

    protected:
        Entity createEntity()
        {
            auto e = Entity(registry.create(), &registry);
            e.addComponent<TransformComponent>();
            return e;
        };

        SceneManager* sceneManager;
        Color backgroundColor = BLACK;
    };
};