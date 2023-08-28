#include "engine.hpp"

class Ball : public Interface {
public:
    Ball(Vector2 pos, Vector2 spd, Engine* eng);
    ~Ball();

    void update();
    void render();

    unsigned int getID();
private:
    Vector2 pos;
    Vector2 spd;

    unsigned int id;
};
