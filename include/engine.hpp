#pragma once
#include <vector>
#include "interface.hpp"

class Engine {
public:
    Engine(unsigned int height, float aspectRatio);
    ~Engine();
    void start();

    unsigned int getScreenWidth() const;
    unsigned int getScreenHeight() const;

    void removeObject(unsigned int id);
private:
    void update();
    void render();
private:
    const float aspectRatio;
    const unsigned int width;
    const unsigned int height;

    std::vector<Interface*> objList;
};
