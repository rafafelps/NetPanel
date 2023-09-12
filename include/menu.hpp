#pragma once
#include <string>
#include "Interface.hpp"
#include "Button.hpp"
#include "Dataset.hpp"
#include "NeuralNetwork.hpp"

enum state {
    NONE,
    TRAIN,
    DRAW,
    ERRORS
};

class Engine;

class Menu : public Interface {
public:
    Menu(Engine* eng);
    ~Menu();

    void update();
    void render();

    std::string getModelName() const;
    NeuralNetwork* getGlobalNetwork();
    
    void setEngine(Engine* eng);
    void setModelName(std::string s);
    void setNewGlobalNet(NeuralNetwork* net);
    
    Interface* showNewMenu(enum state state);
private:
    void initButtons();
private:
    std::string modelName;
    enum state state;

    Engine* eng;
    Button buttons[3];
    Dataset mnistTraining;
    Dataset mnistTest;
    NeuralNetwork* globalNetwork;
    Interface* currentMenu;
};
