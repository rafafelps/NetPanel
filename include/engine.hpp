#pragma once
#include <vector>
#include "interface.hpp"

class Engine {
public:
    Engine(const int width, const int height = 1080, const float aspectRatio = 16.0 / 9.0);
    ~Engine();

    void start();
    unsigned int pushObject(Interface* obj);
    void removeObject(unsigned int pos);
private:
    void update();
    void render();
private:
    const float aspectRatio;
    const int width;
    const int height;

    std::vector<Interface*> objList;
};
