#pragma once
#include <vector>
#include "Interface.hpp"
#include "Menu.hpp"

class Engine {
public:
    Engine(unsigned int height, float aspectRatio);
    ~Engine();
    void start();

    unsigned int getScreenWidth() const;
    unsigned int getScreenHeight() const;
private:
    void update();
    void render();
private:
    const float aspectRatio;
    const unsigned int width;
    const unsigned int height;

    std::vector<Interface*> objList;
    Menu menu;
};
