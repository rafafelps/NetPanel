#include "TrainMenu.hpp"
#include "Engine.hpp"

TrainMenu::TrainMenu(Engine* eng) {
    this->eng = eng;
    epochs = 0;
    data = 0;
    accuracy = 0;

    initButtons();
}

TrainMenu::~TrainMenu() {
    if (localNetwork)
        delete localNetwork;
}

void TrainMenu::update() {

}

void TrainMenu::render() {
    for (int i = START; i <= SAVE; i++) {
        buttons[i].render();
    }

    float menuBorder = eng->getScreenWidth() * 0.25;
    float trMenuWidth = eng->getScreenWidth() * 0.75;
    float trMenuCenterX = menuBorder + trMenuWidth * 0.5;
    float third = trMenuWidth / 3.f;
    DrawLine(menuBorder + third, 0, menuBorder + third, eng->getScreenHeight(), RED);
    DrawLine(menuBorder + 2 * third, 0, menuBorder + 2 * third, eng->getScreenHeight(), RED);
    DrawLine(trMenuCenterX, 0, trMenuCenterX, eng->getScreenHeight(), RED);
}

void TrainMenu::initButtons() {
    for (int i = START; i <= SAVE; i++) {
        buttons[i].setEngine(eng);
        buttons[i].setFontSize(32);
    }

    float menuBorder = eng->getScreenWidth() * 0.25f;
    float trMenuWidth = eng->getScreenWidth() * 0.75f;
    float trMenuCenterX = menuBorder + trMenuWidth * 0.5f;
    float third = trMenuWidth / 3.f;

    Rectangle pos = {third + menuBorder, eng->getScreenHeight() * 0.5f, 125, 50};
    pos.x -= pos.width * 0.5f;
    buttons[START].setPosition(pos);

    pos = {2 * third + menuBorder, eng->getScreenHeight() * 0.5f, 125, 50};
    pos.x -= pos.width * 0.5f;
    buttons[STOP].setPosition(pos);

    pos = {trMenuCenterX, eng->getScreenHeight() - 54.f, 100, 50};
    pos.x -= pos.width * 0.5;
    buttons[LOAD].setPosition(pos);

    pos.x -= (2 * pos.width * 0.5 + pos.width * 0.3);
    buttons[NEW].setPosition(pos);

    pos.x = trMenuCenterX;
    pos.x += (pos.width * 0.5 + pos.width * 0.3);
    buttons[SAVE].setPosition(pos);

    buttons[START].setText("start");
    buttons[STOP].setText("stop");
    buttons[NEW].setText("new");
    buttons[LOAD].setText("load");
    buttons[SAVE].setText("save");
}
