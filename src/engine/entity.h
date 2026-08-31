#pragma once

#include <entt/entt.hpp>
#include "defs.h"

namespace Engine
{
    class Entity
    {
    public:
        Entity() : m_entity(entt::null), m_registry(nullptr) {}
        Entity(entt::entity handle, entt::registry *registry) : m_entity(handle), m_registry(registry) {};

        template <typename T>
        bool hasComponent()
        {
            return m_registry->any_of<T>(m_entity);
        };

        template <typename T, typename... Args>
        T &addComponent(Args &&...args)
        {
            ASSERT(!hasComponent<T>(), "Entity already has component!");

            return m_registry->emplace<T>(m_entity, std::forward<Args>(args)...);
        }

        template <typename T>
        T &getComponent()
        {
            ASSERT(hasComponent<T>(), "Entity does not have component!");

            return m_registry->get<T>(m_entity);
        }

        template <typename T>
        void removeComponent()
        {
            ASSERT(hasComponent<T>(), "Entity does not have component!");

            m_registry->erase<T>(m_entity);
        }

    private:
        entt::entity m_entity;
        entt::registry *m_registry;
    };
};