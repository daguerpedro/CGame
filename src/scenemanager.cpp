#include "scenemanager.h"

namespace Engine
{
    void SceneManager::changeScene(std::unique_ptr<Scene> newScene)

    {

        if (m_activeScene)

            m_activeScene->stop();

        m_activeScene = std::move(newScene);

        m_activeScene->start();

        Logger::Info("[SCENE MANAGER] Carregado cena \"{}\"", m_activeScene->name.c_str());
    };

    void SceneManager::changeScene(const std::string &name)

    {

        if (m_sceneRegistry.find(name) != m_sceneRegistry.end())

            changeScene(m_sceneRegistry[name]());

        else

            Logger::Error("[SCENE MANAGER] Erro ao carregar cena \"{}\": cena não encontrada no registro de cenas.", name.c_str());
    }

    void SceneManager::update(float deltaTime)

    {

        if (m_activeScene)

            m_activeScene->update(*this, deltaTime);
    };

    void SceneManager::draw()

    {

        if (m_activeScene)

        {

            ClearBackground(m_activeScene->backgroundColor);

            m_activeScene->draw();
        }
    };

    bool SceneManager::hasActiveScene()

    {

        return m_activeScene != nullptr;
    };

};