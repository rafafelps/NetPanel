#include "ball.hpp"

#define RADIUS 4

static unsigned int amount = 0;

Ball::Ball(Vector2 pos, Vector2 spd, Engine* eng) {
    this->pos = pos;
    this->spd = spd;
    this->eng = eng;
    id = Interface::amount++;
}

Ball::~Ball() {
    pos.x = 0 - RADIUS;
    pos.y = 0 - RADIUS;
    eng->removeObject(id);
}

void Ball::update() {
    pos.x += spd.x;
    pos.y += spd.y;

    if (pos.x - RADIUS <= 0 || pos.x + RADIUS >= eng->getScreenWidth()) {
        spd.x *= -1;
    }
    if (pos.y - RADIUS <= 0 || pos.y + RADIUS >= eng->getScreenHeight()) {
        spd.y *= -1;
    }
}

void Ball::render() {
    DrawCircleV(pos, RADIUS, BLUE);
}
