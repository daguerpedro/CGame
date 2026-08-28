#pragma once
/* 
    CLASSE TEMPORARIA PARA TESTES INICIAIS DO ENTT
*/
#include <raylib.h>

struct Position
{
    float x;
    float y;
};

struct Velocity
{
    float x;
    float y;
};

struct Renderable
{
    Vector2 size;
    float rotation;
    float scale;
    Color color;
};
