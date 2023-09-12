#include "Menu.hpp"
#include "Engine.hpp"
#include "TrainMenu.hpp"
#include "DrawMenu.hpp"
#include "ErrorsMenu.hpp"

#include <iostream>

#define BUTTON_MARGIN eng->getScreenWidth() * 0.25f * 0.07f

Menu::Menu(Engine* eng) {
    this->eng = eng;
    globalNetwork = nullptr;
    currentMenu = nullptr;
    modelName = "";

    mnistTraining.setData("dataset/mnist/training/train-labels.idx1-ubyte",
                          "dataset/mnist/training/train-images.idx3-ubyte");
    mnistTest.setData("dataset/mnist/test/t10k-labels.idx1-ubyte",
                      "dataset/mnist/test/t10k-images.idx3-ubyte");

    initButtons();
}

Menu::~Menu() {
    if (currentMenu)
        delete currentMenu;
        
    if (globalNetwork)
        delete globalNetwork;
}

void Menu::update() {
    for (int i = 0; i < 3; i++) {
        if (buttons[i].clicked()) {
            if (buttons[i++].select(true)) {
                // Botao jah apertado selecionado 2 vezes
                return;
            }

            currentMenu = showNewMenu((enum state)i);

            for (int j = 0; j < 2; j++) {
                if (i >= 3) { i = 0; }
                buttons[i++].select(false);
            }

            break;
        }
    }

    if (currentMenu)
        currentMenu->update();
}

void Menu::render() {
    DrawRectangle(0, 0, eng->getScreenWidth() * 0.25, eng->getScreenHeight(), (Color){128, 128, 128, 255});
    
    for (int i = 0; i < 3; i++) {
        buttons[i].render();
    }

    if (currentMenu)
        currentMenu->render();
}

std::string Menu::getModelName() const {
    return modelName;
}

NeuralNetwork* Menu::getGlobalNetwork() {
    return globalNetwork;
}

void Menu::setEngine(Engine* eng) {
    this->eng = eng;
}

void Menu::setModelName(std::string s) {
    modelName = s;
}

void Menu::setNewGlobalNet(NeuralNetwork* net) {
    globalNetwork = net;
}

Interface* Menu::showNewMenu(enum state state) {
    if (currentMenu)
        delete currentMenu;

    if (state == TRAIN) {
        return new TrainMenu(eng, this, &mnistTraining);
    } else if (state == DRAW) {
        return new DrawMenu(eng);
    } else if (state == ERRORS) {
        return new ErrorsMenu(eng);
    }

    return nullptr;
}

void Menu::initButtons() {
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
