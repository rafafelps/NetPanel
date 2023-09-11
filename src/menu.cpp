#include "menu.hpp"
#include "engine.hpp"

#define BUTTON_MARGIN (float)(eng->getScreenWidth()) * (float)(0.25) * (float)(0.07)

Menu::Menu(Engine* eng) :
state(NONE) {
    this->eng = eng;

    for (int i = 0; i < 3; i++) {
        buttons[i].setEngine(eng);
    }

    Rectangle pos = {BUTTON_MARGIN, BUTTON_MARGIN, BUTTON_MARGIN / (float)(0.07) - (2 * BUTTON_MARGIN), (eng->getScreenHeight() - (4 * BUTTON_MARGIN)) / 3};
    buttons[0].setPosition(pos);

    for (int i = 1; i < 3; i++) {
        pos.y += pos.height + BUTTON_MARGIN;
        buttons[i].setPosition(pos);
    }

    buttons[0].setText("Train");
    buttons[1].setText("Draw");
    buttons[2].setText("Errors");
}

Menu::~Menu() {}

void Menu::update() {
    for (int i = 0; i < 3; i++) {
        if (buttons[i].clicked()) {
            if (buttons[i++].select(true)) {
                // Botao jah apertado selecionado 2 vezes
                return;
            }

            for (int j = 0; j < 2; j++) {
                if (i >= 3) { i = 0; }
                buttons[i++].select(false);
            }

            break;
        }
    }
}

void Menu::render() {
    DrawRectangle(0, 0, eng->getScreenWidth() * 0.25, eng->getScreenHeight(), (Color){128, 128, 128, 255});
    
    for (int i = 0; i < 3; i++) {
        buttons[i].render();
    }
}

void Menu::setEngine(Engine* eng) {
    this->eng = eng;
}
