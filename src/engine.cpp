#include "engine.hpp"

Engine::Engine(const int width, const int height, const float aspectRatio) :
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

unsigned int Engine::pushObject(Interface* obj) {
    objList.push_back(obj);
    return objList.size() - 1;
}

void Engine::removeObject(unsigned int pos) {
    objList.erase(objList.begin() + pos);
}
