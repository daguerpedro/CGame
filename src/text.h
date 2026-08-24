#pragma once
#include <string>
#include <raylib.h>

class Text
{

public:
    Text(std::string txt, Vector2 position, float fontSize, Color color)
        : text(txt), pos(position), fontSize(fontSize), color(color) {};

    Vector2 pos;
    float fontSize;
    Color color;
    std::string text;

    void draw() {
        DrawText(text.c_str(), pos.x, pos.y, fontSize, color);
    };
};