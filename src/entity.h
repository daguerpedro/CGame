#pragma once
#include <raylib.h>

class Entity
{
protected:
    Vector2 pos;

    float size;
    float scale;
    float rotation;

    Color col;

public:
    Entity() : pos({0,0}), size(1), scale(1), rotation(0), col(BLACK)
    {

    };
    
    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    void setSize(float size);
    float getSize();

    void setPosition(Vector2 position);
    Vector2 getPosition();

    void setScale(float scale);
    float getScale();

    void rotate(float degres);
    void setRotation(float rotation);
    float getRotation();

    void setColor(Color color);
    Color getColor();
};
