#pragma once

#include <memory>
#include <functional>
#include <unordered_map>

#include "scene.h"
#include "logger.h"

namespace Engine
{
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

        bool hasActiveScene();

        const std::string &getActiveSceneName()
        {
            return m_activeScene->name;
        };

        float getViewWidth() const
        {
            return viewWidth;
        }

        float getViewHeight() const
        {
            return viewHeight;
        }
        
private:
        friend class App;
        friend class Editor;
        friend class Renderer;
        
        void update(float deltaTime);

        const auto &getRegisteredScenes() const { return m_sceneRegistry; }
        const auto activeScene() { return m_activeScene.get(); }

        float viewWidth = 0;
        float viewHeight = 0;
    };
}
