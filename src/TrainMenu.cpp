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
    if (localNetwork) {
        localNetwork->setLearn(false);
        if (learnThread)
            learnThread->join();

        mn->setNewGlobalNet(localNetwork);
    }
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
        accuracy = localNetwork->getCorrectPredictions() / (static_cast<float>(totalData) + 1e-10f);
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
    float biggerFontSize = 60.f / 720.f * eng->getScreenHeight();
    float trMenuCenterX = menuBorder + trMenuWidth * 0.5;
    Vector2 topTextSize = {trMenuWidth / 6.f, eng->getScreenHeight() * 0.05f};
    
    std::string s = std::to_string(epoch);
    DrawText("EPOCHS", menuBorder + topTextSize.x - MeasureText("EPOCHS", fontSize) * 0.5f, topTextSize.y, fontSize, (Color){158, 158, 158, 255});
    DrawText(s.c_str(), menuBorder + topTextSize.x - MeasureText(s.c_str(), fontSize) * 0.5f, eng->getScreenHeight() * 0.1f, fontSize, (Color){158, 158, 158, 255});

    s = std::to_string(data);
    DrawText("DATA", menuBorder + topTextSize.x * 5.f - MeasureText("DATA", fontSize) * 0.5f, topTextSize.y, fontSize, (Color){158, 158, 158, 255});
    DrawText(s.c_str(), menuBorder + topTextSize.x * 5.f - MeasureText(s.c_str(), fontSize) * 0.5f, eng->getScreenHeight() * 0.1f, fontSize, (Color){158, 158, 158, 255});

    s = std::to_string(accuracy + 0.00005);
    s = s.substr(0, s.find(".") + 5);
    DrawText("ACCURACY", trMenuCenterX - MeasureText("ACCURACY", biggerFontSize) * 0.5f, eng->getScreenHeight() * 0.1f, biggerFontSize, (Color){158, 158, 158, 255});
    DrawText(s.c_str(), trMenuCenterX - MeasureText(s.c_str(), biggerFontSize) * 0.5f, (eng->getScreenHeight() * 0.5f - (eng->getScreenHeight() * 0.1f + biggerFontSize)) * 0.5f + eng->getScreenHeight() * 0.1f + biggerFontSize * 0.5f, biggerFontSize, (Color){158, 158, 158, 255});

    float third = trMenuWidth / 3.f;
    DrawLine(menuBorder + third, 0, menuBorder + third, eng->getScreenHeight(), RED);
    DrawLine(menuBorder + 2 * third, 0, menuBorder + 2 * third, eng->getScreenHeight(), RED);
    DrawLine(trMenuCenterX, 0, trMenuCenterX, eng->getScreenHeight(), RED);
    DrawLine(menuBorder + third/2, 0, menuBorder + third/2, eng->getScreenHeight(), RED);
    DrawLine(menuBorder + 5 * third / 2.f, 0, menuBorder + 5 * third / 2.f, eng->getScreenHeight(), RED);
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
    if (!localNetwork->getLearningStatus()) {
        if (learnThread) {
            learnThread->join();
            delete learnThread;
            learnThread = nullptr;
        }
    }

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
    if (localNetwork) {
        localNetwork->setLearn(false);
        if (learnThread) {
            learnThread->join();
            delete learnThread;
            learnThread = nullptr;
        }
        delete localNetwork;
    }

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

    if (localNetwork) {
        localNetwork->setLearn(false);
        if (learnThread) {
            learnThread->join();
            delete learnThread;
            learnThread = nullptr;
        }
        delete localNetwork;
    }

    localNetwork = new NeuralNetwork();
    localNetwork->setDataset(mnist);
    localNetwork->setName(path);
    localNetwork->loadNetworkState();

    mn->setModelName("first");
}

void TrainMenu::saveNetwork() {
    if (localNetwork)
        localNetwork->saveNetworkState();
}
