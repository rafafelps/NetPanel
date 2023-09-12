#include <vector>
#include <string>
#include "TrainMenu.hpp"
#include "Engine.hpp"

TrainMenu::TrainMenu(Engine* eng, Menu* mn, Dataset* mnist) {
    this->eng = eng;
    this->mn = mn;
    epoch = 0;
    data = 0;
    accuracy = 0;
    localNetwork = mn->getGlobalNetwork();
    this->mnist = mnist;
    learnThread = nullptr;

    initButtons();
}

TrainMenu::~TrainMenu() {
    localNetwork->setLearn(false);
    if (learnThread)
        learnThread->join();

    if (localNetwork)
        mn->setNewGlobalNet(localNetwork);
}

void TrainMenu::update() {
    int i;
    if (!localNetwork)
        i = NEW;
    else
        i = START;

    for (; i <= SAVE; i++) {
        if (buttons[i].clicked()) {
            switch (i) {
                case START:
                    startNetwork();
                    break;
                case STOP:
                    localNetwork->setLearn(false);
                    if (learnThread) {
                        learnThread->join();
                        delete learnThread;
                        learnThread = nullptr;
                    }
                    break;
                case NEW:
                    createNewNetwork();
                    break;
                case LOAD:
                    loadNetwork();
                    break;
                case SAVE:
                    saveNetwork();
                    break;
                default:
                    break;
            }
            break;
        }
    }

    if (localNetwork) {
        epoch = localNetwork->getCurrentEpoch();
        data = localNetwork->getCurrentData();
        unsigned int totalData = data;
        if (epoch > 0) {
            totalData += epoch * mnist->getSize();
        }
        accuracy = localNetwork->getCorrectPredictions() / static_cast<float>(totalData);
    }
}

void TrainMenu::render() {
    int i;
    if (!localNetwork)
        i = NEW;
    else
        i = START;

    for (; i <= SAVE; i++) {
        buttons[i].render();
    }

    float menuBorder = eng->getScreenWidth() * 0.25;
    float trMenuWidth = eng->getScreenWidth() * 0.75;
    float fontSize = 32.f / 720.f * eng->getScreenHeight();
    std::string s = std::to_string(epoch);
    DrawText(s.c_str(), (trMenuWidth * 0.15f + menuBorder) - (MeasureText(s.c_str(), fontSize) / 2.f), eng->getScreenHeight() * 0.05f, fontSize, (Color){158, 158, 158, 255});

    float trMenuCenterX = menuBorder + trMenuWidth * 0.5;
    float third = trMenuWidth / 3.f;
    DrawLine(menuBorder + third, 0, menuBorder + third, eng->getScreenHeight(), RED);
    DrawLine(menuBorder + 2 * third, 0, menuBorder + 2 * third, eng->getScreenHeight(), RED);
    DrawLine(trMenuCenterX, 0, trMenuCenterX, eng->getScreenHeight(), RED);
}

void TrainMenu::initButtons() {
    float fontSize = 32.f / 720.f * eng->getScreenHeight();
    for (int i = START; i <= SAVE; i++) {
        buttons[i].setEngine(eng);
        buttons[i].setFontSize(fontSize);
    }

    float menuBorder = eng->getScreenWidth() * 0.25f;
    float trMenuWidth = eng->getScreenWidth() * 0.75f;
    float trMenuCenterX = menuBorder + trMenuWidth * 0.5f;
    float third = trMenuWidth / 3.f;
    Vector2 szButtons = {125.f / 720.f * eng->getScreenHeight(), 50.f / 720.f * eng->getScreenHeight()};

    Rectangle pos = {third + menuBorder, eng->getScreenHeight() * 0.5f, szButtons.x, szButtons.y};
    pos.x -= pos.width * 0.5f;
    buttons[START].setPosition(pos);

    pos = {2 * third + menuBorder, eng->getScreenHeight() * 0.5f, szButtons.x, szButtons.y};
    pos.x -= pos.width * 0.5f;
    buttons[STOP].setPosition(pos);

    szButtons = {100.f / 720.f * eng->getScreenHeight(), 50.f / 720.f * eng->getScreenHeight()};
    pos = {trMenuCenterX, eng->getScreenHeight() - szButtons.y - 4.f, szButtons.x, szButtons.y};
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

void TrainMenu::startNetwork() {
    if (learnThread)
        return;

    localNetwork->setLearn(true);
    
    // if (!checkBox)
    // New Thread Here
    learnThread = new std::thread(&NeuralNetwork::learn, localNetwork, 1);

    // else
    // localNet->propagate
    // backpropagate
    // etc...
}

void TrainMenu::createNewNetwork() {
    if (localNetwork)
        delete localNetwork;

    std::vector<unsigned int> v;
    v.push_back(mnist->getWidth() * mnist->getHeight());
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    localNetwork = new NeuralNetwork(v);
    localNetwork->setDataset(mnist);
    localNetwork->setName("first");
    localNetwork->kaimingInitialization();

    mn->setModelName("first");
}

void TrainMenu::loadNetwork() {
    // Abrir seletor de arquivo do windows
    std::string path = "first";

    if (localNetwork)
        delete localNetwork;

    localNetwork = new NeuralNetwork();
    localNetwork->setName(path);
    localNetwork->loadNetworkState();

    mn->setModelName("first");
}

void TrainMenu::saveNetwork() {
    if (localNetwork)
        localNetwork->saveNetworkState();
}
