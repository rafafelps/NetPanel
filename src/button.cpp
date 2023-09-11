#include "button.hpp"
#include "engine.hpp"

#include <iostream>

Button::Button() :
isSelected(false) {}

Button::~Button() {
    eng = nullptr;
}

void Button::update() {}

void Button::render() {
    if (!isSelected) {
        DrawRectangleRoundedLines(position, 0.2, 20, 4, (Color){158, 158, 158, 255});
        DrawText(text.c_str(), position.x + (position.width - MeasureText(text.c_str(), fontSize)) * 0.5, position.y + (position.height * 0.5) - (fontSize * 0.45), fontSize, (Color){158, 158, 158, 255});
    } else {
        DrawRectangleRounded(position, 0.2, 20, (Color){158, 158, 158, 255});
        DrawText(text.c_str(), position.x + (position.width - MeasureText(text.c_str(), fontSize)) * 0.5, position.y + (position.height * 0.5) - (fontSize * 0.45), fontSize, (Color){128, 128, 128, 255});
    }
}

bool Button::clicked() const {
    if (!IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        return false;

    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= position.x &&
        mousePos.y >= position.y &&
        mousePos.x <= position.x + position.width &&
        mousePos.y <= position.y + position.height) {
        return true;
    }

    return false;
}

bool Button::select(bool option) {
    if (isSelected && option) { return true; }
    isSelected = option;
    return false;
}

void Button::setEngine(Engine* eng) {
    this->eng = eng;
    fontSize = (60.0 / 720.0) * eng->getScreenHeight();
}

void Button::setPosition(Rectangle pos) {
    position = pos;
}

void Button::setText(std::string txt) {
    text = txt;
}

