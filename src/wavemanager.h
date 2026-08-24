#pragma once
#include <vector>
#include "enemy.h"

class WaveManager
{
private:
    int wave;

    std::vector<Enemy> enemies;
public:
    WaveManager()
    {
        wave = 0;
        enemies = std::vector<Enemy>();
    };

    int getWave();
    int getEnemies();

    void reset();
    void startNextWave();
    void update(float dt);
};

