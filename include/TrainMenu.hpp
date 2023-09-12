#pragma once
#include "interface.hpp"
#include "button.hpp"
#include "NeuralNetwork.hpp"

enum btTypes {
    START,
    STOP,
    NEW,
    LOAD,
    SAVE
};

class Engine;

class TrainMenu : public Interface {
public:
    TrainMenu(Engine* eng);
    ~TrainMenu();

    void update();
    void render();
private:
    void initButtons();
private:
    unsigned int epochs;
    unsigned int data;
    float accuracy;
    Button buttons[5];
    Engine* eng;
    NeuralNetwork* localNetwork;
};
