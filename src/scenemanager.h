#pragma once

#include <memory>
#include "scene.h"
#include <unordered_map>
#include <functional>

class SceneManager
{
private:
    std::unique_ptr<Scene> m_activeScene;
    std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>> m_sceneRegistry;

public:
    SceneManager() { };

    template<typename T>
    void registerScene(const std::string& name) {
        m_sceneRegistry[name] = []() { 
            return std::make_unique<T>(); 
        };
    }

    void changeScene(std::unique_ptr<Scene> newScene)
    {
        if (m_activeScene)
            m_activeScene->stop();

        m_activeScene = std::move(newScene);
        m_activeScene->start();
    };

    void changeScene(const std::string& name) 
    {
        if (m_sceneRegistry.find(name) != m_sceneRegistry.end()) 
            changeScene(m_sceneRegistry[name]());
        else
            printf_s("[SCENEMANAGER] Erro ao carregar cena \"%s\": cena não encontrada no registro de cenas.\n");
    }

    void update(float deltaTime)
    {
        if (m_activeScene)
            m_activeScene->update(*this, deltaTime);
    };

    void draw()
    {
        if (m_activeScene)
        {
            ClearBackground(m_activeScene->backgroundColor);
            m_activeScene->draw();
        }
    };

    bool hasActiveScene()
    {
        return m_activeScene != nullptr;
    };

    const std::string &getActiveSceneName()
    {
        return m_activeScene->name;
    };

    const auto& getRegisteredScenes() const { return m_sceneRegistry; }
};
