#include "tower.h"
#include <cmath>
#include <cstdio>

void Tower::draw() 
{
    DrawRectangle(pos.x, pos.y, size * scale, size * scale, col);
}

void Tower::update(float dt)
{

};