#pragma once
#include "Interface.hpp"

class Engine;

class ErrorsMenu : public Interface {
public:
    ErrorsMenu(Engine* eng);
    ~ErrorsMenu();

    void update();
    void render();
private:
    Engine* eng;
};
