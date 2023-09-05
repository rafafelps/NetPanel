#pragma once
#include <string>
#include "interface.hpp"

class Engine;

class Button : public Interface {
public:
    Button();
    ~Button();

    void update();
    void render();

    void setEngine(Engine* eng);
    void setPosition(Vector2 pos);
    void setText(std::string txt);

private:
    Engine* eng;
    Vector2 position;
    std::string text;
};
