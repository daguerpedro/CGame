#pragma once
#include <raylib.h>
#include "entity.h"

class Tower : public Entity
{
private:
public:
    Tower() : Entity()
    {

    };
    
    void update(float dt) override;
    void draw() override;
};
