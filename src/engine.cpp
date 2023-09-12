#include "Engine.hpp"

Engine::Engine(unsigned int height, float aspectRatio) :
aspectRatio(aspectRatio),
width(height * aspectRatio),
height(height),
menu(this) {
    InitWindow(this->width, this->height, "NetPanel");
    SetTargetFPS(60);


    objList.push_back(&menu);
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

    EndDrawing();
}
