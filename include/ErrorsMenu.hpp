#pragma once
#include "Interface.hpp"
#include "NeuralNetwork.hpp"
#include "Menu.hpp"
#include "Dataset.hpp"

class Engine;

class ErrorsMenu : public Interface {
public:
    ErrorsMenu(Engine* eng, Menu* mn, Dataset* mnist);
    ~ErrorsMenu();

    void update();
    void render();
private:
    void findNextError();
private:
    unsigned int currData;
    unsigned int predValue;
    unsigned int trueValue;
    bool foundError;

    Engine* eng;
    NeuralNetwork* globalNetwork;
    Menu* mn;
    Dataset* mnist;
    Texture2D texture;
    Vector2 size;
};
