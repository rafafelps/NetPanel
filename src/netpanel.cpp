#include "netpanel.hpp"

Netpanel::Netpanel() :
isRunning(false) {}

Netpanel::~Netpanel() {}

void Netpanel::start(unsigned int height, float aspectRatio) {
    if (isRunning) { return; }
    engine = new Engine(height, aspectRatio);

    engine->start();
    isRunning = true;
}
