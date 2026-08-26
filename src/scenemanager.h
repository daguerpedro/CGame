#pragma once

#include <vector>
#include <memory>

#include "scene.h"

class SceneManager
{
private:
    std::vector<std::string, std::unique_ptr<Scene>> m_scenes;

public:
    void changeScene() { };
    void update(float deltaTime) { };
    void draw() { };
};
