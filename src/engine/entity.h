#pragma once

#include <entt/entt.hpp>
#include  "defs.h"

namespace Engine
{
    class Scene;
    class Entity
    {
    public:
        Entity(entt::entity handle, Scene *scene) : m_entity(handle), m_scene(scene) {};

        template <typename T>
        bool hasComponent()
        {
            return m_scene->registry.any_of<T>(m_entity);
        };

        template <typename T, typename... Args>
        T &addComponent(Args &&...args)
        {
            ASSERT(!hasComponent<T>(), "Entity already has component!");

            return m_scene->registry.emplace<T>(m_entity, std::forward<Args>(args)...);
        }

        template <typename T>
        T &getComponent()
        {
            ASSERT(hasComponent<T>(), "Entity does not have component!");

            return m_scene->registry.get<T>(m_entity);
        }

        template <typename T>
        T &removeComponent()
        {
            ASSERT(hasComponent<T>(), "Entity does not have component!");

            return m_scene->registry.erase<T>(m_entity);
        }

    private:
        entt::entity m_entity;
        Scene *m_scene;
    };
};