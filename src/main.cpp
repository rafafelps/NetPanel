#include <iostream>
#include <raylib.h>
#include "netpanel.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        // TODO: resolution menu
        std::cout << "Error!" << std::endl;
        std::cout << "Usage: " << argv[0] << " " << "{resolution}" << std::endl;
        return 1;
    }
    const float aspectRatio = 16.0 / 9;
    const int height = atoi(argv[1]);
    const int width = height * aspectRatio;
    
    Netpanel app;
    app.start(height, aspectRatio);

    return 0;
}
