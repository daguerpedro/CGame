#include "enemy.h"

void Enemy::draw()
{
    DrawRectangle(pos.x, pos.y, size * scale, size * scale, col);
};

void Enemy::update(float dt) 
{

};