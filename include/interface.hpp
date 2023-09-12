#pragma once
#include <raylib.h>

class Interface {
public:
    virtual ~Interface() {};
    virtual void update() = 0;
    virtual void render() = 0;
};
