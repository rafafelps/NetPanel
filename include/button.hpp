#pragma once
#include <string>
#include "interface.hpp"

class Engine;

class Button : public Interface {
public:
    Button();
    ~Button();

    void update();
    void render();

    bool clicked() const;
    bool select(bool option);

    void setEngine(Engine* eng);
    void setPosition(Rectangle pos);
    void setText(std::string txt);

private:
    Engine* eng;
    Rectangle position;
    std::string text;
    unsigned char fontSize;
    bool isSelected;
};
