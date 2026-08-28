#pragma once

#include <memory>
#include <functional>
#include <unordered_map>

#include "scene.h"
#include "logger.h"

class SceneManager
{
private:
    std::unique_ptr<Scene> m_activeScene;
    std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>> m_sceneRegistry;

public:
    SceneManager() {};

    template <typename T>
    void registerScene(const std::string &name)
    {
        m_sceneRegistry[name] = []()
        {
            return std::make_unique<T>();
        };
    }

    void changeScene(std::unique_ptr<Scene> newScene);

    void changeScene(const std::string &name);

    void update(float deltaTime);

    void draw();

    bool hasActiveScene();

    const std::string &getActiveSceneName()
    {
        return m_activeScene->name;
    };

    const auto &getRegisteredScenes() const { return m_sceneRegistry; }
};
