#pragma once
#include <raylib.h>

class Interface {
public:
    virtual ~Interface() = 0;
    virtual void update() {}
    virtual void render() {}
};
