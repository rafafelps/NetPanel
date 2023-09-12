#pragma once
#include "Engine.hpp"

class Netpanel {
public:
    Netpanel();
    ~Netpanel();
    void start(unsigned int height = 1080, float aspectRatio = 16.0 / 9.0);
private:
    Engine* engine;
    bool isRunning;
};
