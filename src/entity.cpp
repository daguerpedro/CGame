#include "entity.h"

#include <cmath>
#include <cstdio>

void Entity::setSize(float size)
{
    this->size = size;
};

float Entity::getSize()
{
    return this->size;
};

void Entity::setPosition(Vector2 position)
{
    this->pos = position;
};

Vector2 Entity::getPosition()
{
    return this->pos;
};

void Entity::setScale(float scale)
{
    this->scale = scale;
};

float Entity::getScale()
{
    return this->scale;
};

void Entity::rotate(float degres)
{
    this->rotation += degres;
};

void Entity::setRotation(float rotation)
{
    this->rotation = rotation;
};

float Entity::getRotation()
{
    return this->rotation;
}

void Entity::setColor(Color color)
{
    this->col = color;
}

Color Entity::getColor()
{
    return this->col;
}