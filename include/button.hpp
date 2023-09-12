#pragma once
#include <string>
#include "Interface.hpp"

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
    void setFontSize(unsigned char size);

private:
    Engine* eng;
    Rectangle position;
    std::string text;
    unsigned char fontSize;
    bool isSelected;
};
