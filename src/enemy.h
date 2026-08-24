#pragma once
#include "entity.h"
#include <raylib.h>

class Enemy : public Entity
{
public:
    Enemy(float life, float damage) : Entity() {
        this->life = life;
        this->damage = damage;
    };

    void draw() override;
    void update(float dt) override;

    float life;
    float damage;
};