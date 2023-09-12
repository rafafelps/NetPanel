#pragma once
#include "interface.hpp"

class Engine;

class DrawMenu : public Interface {
public:
    DrawMenu(Engine* eng);
    ~DrawMenu();

    void update();
    void render();

private:
    Engine* eng;
};
