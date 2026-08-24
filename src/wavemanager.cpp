#include "wavemanager.h"

int WaveManager::getWave()
{
    return this->wave;
};

int WaveManager::getEnemies()
{
    return this->enemies.size();
}

void WaveManager::startNextWave()
{
    if (enemies.empty() == false)
        enemies.clear();

    wave++;
};

void WaveManager::update(float dt)
{
    std::erase_if(enemies, [](const Enemy &enemy){ return enemy.life <= 0.0f; });

    for (auto &enemy : enemies)
    {
        enemy.update(dt);
        enemy.draw();
    }
};

void WaveManager::reset()
{
    wave = 0;
    enemies.clear();
};