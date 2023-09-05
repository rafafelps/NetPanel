#pragma once
#include "interface.hpp"
#include "button.hpp"

#define TRAIN 0
#define DRAW 1
#define ERRORS 2

class Engine;

class Menu : public Interface {
public:
    Menu();
    ~Menu();

    void update();
    void render();

    void setEngine(Engine* eng);
private:
    unsigned char state;
    Engine* eng;
    Button buttons[3];
};
