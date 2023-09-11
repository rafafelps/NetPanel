#pragma once
#include "interface.hpp"
#include "button.hpp"

enum state {
    NONE,
    TRAIN,
    DRAW,
    ERRORS
};

class Engine;

class Menu : public Interface {
public:
    Menu(Engine* eng);
    ~Menu();

    void update();
    void render();

    void setEngine(Engine* eng);
private:
    enum state state;
    Engine* eng;
    Button buttons[3];
};
