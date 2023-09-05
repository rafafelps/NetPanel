#include "button.hpp"

Button::Button() {}

Button::~Button() {
    eng = nullptr;
}

void Button::update() {
    
}

void Button::render() {

}

void Button::setEngine(Engine* eng) {
    this->eng = eng;
}

void Button::setPosition(Vector2 pos) {
    position = pos;
}

void Button::setText(std::string txt) {
    text = txt;
}

