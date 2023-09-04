#include "engine.hpp"

Engine::Engine(unsigned int height, float aspectRatio) :
aspectRatio(aspectRatio),
width(height * aspectRatio),
height(height) {
    InitWindow(this->width, this->height, "NetPanel");
    SetTargetFPS(60);
}

Engine::~Engine() {
    CloseWindow();
}

void Engine::start() {
    while (!WindowShouldClose()) {
        update();
        render();
    }
}

unsigned int Engine::getScreenWidth() const {
    return width;
}

unsigned int Engine::getScreenHeight() const {
    return height;
}

void Engine::removeObject(unsigned int id) {
    unsigned int position = 0;
    for (auto obj : objList) {
        if (obj->getID() == id) {
            objList.erase(objList.begin() + position);
        }
        position++;
    }
}

void Engine::update() {
    for (auto obj : objList) {
        obj->update();
    }
}

void Engine::render() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (auto obj : objList) {
        obj->render();
    }

    DrawFPS(0, 0);
    EndDrawing();
}
