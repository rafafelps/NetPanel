#include "menu.hpp"
#include "engine.hpp"

Menu::Menu() :
state(TRAIN) {
    for (int i = 0; i < 3; i++) {
        buttons[i].setEngine(eng);
        buttons[i].setPosition((Vector2){0,0});
    }
    buttons[0].setText("Train");
    buttons[1].setText("Draw");
    buttons[2].setText("Errors");
}

Menu::~Menu() {}

void Menu::update() {

}

void Menu::render() {
    DrawRectangle(0, 0, eng->getScreenWidth() * 0.25, eng->getScreenHeight(), (Color){128, 128, 128, 255});
}

void Menu::setEngine(Engine* eng) {
    this->eng = eng;
}
