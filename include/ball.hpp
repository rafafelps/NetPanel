#pragma once
#include "engine.hpp"

class Ball : public Interface {
public:
    Ball(Vector2 pos, Vector2 spd, Engine* eng);
    ~Ball();

    void update();
    void render();
private:
    Vector2 pos;
    Vector2 spd;

    Engine* eng;

    unsigned int id;
};
