#include <iostream>
#include <raylib.h>
#include "netpanel.hpp"

int main() {
    const float aspectRatio = 16.0 / 9;
    const int height = 1080;
    const int width = height * aspectRatio;
    
    Netpanel app;
    app.start();

    return 0;
}
