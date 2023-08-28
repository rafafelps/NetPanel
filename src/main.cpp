#include <iostream>
#include <raylib.h>
#include "engine.hpp"

int main() {
    const float aspectRatio = 16.0 / 9;
    const int height = 1080;
    const int width = height * aspectRatio;
    
    Engine engine(width, height, aspectRatio);
    engine.start();

    return 0;
}
