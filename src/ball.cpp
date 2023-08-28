#include "ball.hpp"

Ball::Ball(Vector2 pos, Vector2 spd, Engine* eng) {
    this->pos = pos;
    this->spd = spd;

    id = eng->pushObject(this);
}

Ball::~Ball() {}

void Ball::update() {
    // Ball Collision
}

void Ball::render() {
    DrawCircleV(pos, 4, BLUE);
}

unsigned int Ball::getID() {
    return id;
}
