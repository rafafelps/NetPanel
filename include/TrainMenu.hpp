#pragma once
#include <thread>
#include "interface.hpp"
#include "button.hpp"
#include "NeuralNetwork.hpp"
#include "Dataset.hpp"
#include "Menu.hpp"

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
    TrainMenu(Engine* eng, Menu* mn, Dataset* mnist);
    ~TrainMenu();

    void update();
    void render();
private:
    void initButtons();
    void startNetwork();
    void createNewNetwork();
    void loadNetwork();
    void saveNetwork();
private:
    unsigned int epoch;
    unsigned int data;
    float accuracy;

    Button buttons[5];
    Engine* eng;
    Menu* mn;
    NeuralNetwork* localNetwork;
    Dataset* mnist;
    std::thread* learnThread;
};
