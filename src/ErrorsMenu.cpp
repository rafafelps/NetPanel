#include "ErrorsMenu.hpp"
#include "Engine.hpp"
#include <string>

Image tst;

ErrorsMenu::ErrorsMenu(Engine* eng, Menu* mn, Dataset* mnist) {
    currData = -1;
    predValue = 0;
    trueValue = 0;
    foundError = false;

    this->eng = eng;
    this->mn = mn;
    globalNetwork = mn->getGlobalNetwork();
    this->mnist = mnist;
    size.x = eng->getScreenHeight() * 0.55f - 2;
    size.y = size.x;

    Image img;
    img.width = mnist->getWidth();
    img.height = mnist->getHeight();
    img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    img.mipmaps = 1;

    Color* pixels = new Color[img.width * img.height];
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            pixels[i * img.width + j] = BLACK;
        }
    }
    img.data = pixels;
    ImageResizeNN(&img, size.x, size.y);

    texture = LoadTextureFromImage(img);
    UnloadImage(img);

    initButton();

    if (globalNetwork)
        findNextError();
}

ErrorsMenu::~ErrorsMenu() {
    UnloadTexture(texture);
}

void ErrorsMenu::update() {
    if (!globalNetwork) { return; }

    if (next.clicked()) {
        findNextError();
    }
}

void ErrorsMenu::render() {
    float menuCenterX = eng->getScreenWidth() * 0.75f * 0.5f + eng->getScreenWidth() * 0.25f;
    Rectangle pos = {
        menuCenterX - (size.x + 2) * 0.5f,
        eng->getScreenHeight() * 0.08f,
        size.x + 2,
        size.y + 2
    };

    DrawRectangleLines(pos.x, pos.y, pos.width, pos.height, (Color){158, 158, 158, 255});
    DrawTexture(texture, pos.x + 1, pos.y + 1, WHITE);
    
    float predAlign = eng->getScreenWidth() * 0.25f + (pos.x - eng->getScreenWidth() * 0.25f) * 0.5f;
    float labelAlign = (pos.x + pos.width) + ((eng->getScreenWidth()) - (pos.x + pos.width)) * 0.5f;
    float yCenter = pos.y + pos.height * 0.5f;
    float fontSize = 30.f / 720.f * eng->getScreenHeight();
    float delta = 20.f / 720.f * eng->getScreenHeight();

    std::string s = "PREDICTED";
    DrawText(s.c_str(), predAlign - MeasureText(s.c_str(), fontSize) * 0.5f, yCenter - delta - fontSize * 0.5f, fontSize, (Color){158, 158, 158, 255});
    if (globalNetwork)
        s = std::to_string(predValue);
    else
        s = "x";
    DrawText(s.c_str(), predAlign - MeasureText(s.c_str(), fontSize) * 0.5f, yCenter + delta, fontSize, (Color){158, 158, 158, 255});
    

    s = "LABEL";
    DrawText(s.c_str(), labelAlign - MeasureText(s.c_str(), fontSize) * 0.5f, yCenter - delta - fontSize * 0.5f, fontSize, (Color){158, 158, 158, 255});
    if (globalNetwork)
        s = std::to_string(trueValue);
    else
        s = "x";
    DrawText(s.c_str(), labelAlign - MeasureText(s.c_str(), fontSize) * 0.5f, yCenter + delta, fontSize, (Color){158, 158, 158, 255});

    if (globalNetwork)
        next.render();
}

// Maybe new thread
void ErrorsMenu::findNextError() {
    unsigned int dataSize = mnist->getSize();
    for (currData++; currData < dataSize; currData++) {
        unsigned int label = mnist->data[currData]->label;

        globalNetwork->propagate(mnist->data[currData]->values);
        
        unsigned int predicted;
        delete globalNetwork->getResults(&predicted);

        if (predicted != label) {
            predValue = predicted;
            trueValue = label;
            foundError = true;
            break;
        }
    }

    if (currData == dataSize) { currData = -1; findNextError(); }

    unsigned int height = mnist->getHeight();
    unsigned int width = mnist->getWidth();
    
    Image img;
    img.width = width;
    img.height = height;
    img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    img.mipmaps = 1;

    Color* pixels = new Color[width * height];
    
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            unsigned char grayScale = mnist->data[currData]->values[i * width + j] * 255.f;
            pixels[i * width + j] = (Color){grayScale, grayScale, grayScale, 255};
        }
    }

    img.data = pixels;
    ImageResizeNN(&img, size.x, size.y);
    tst = img;
    UnloadTexture(texture);
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void ErrorsMenu::initButton() {
    next.setEngine(eng);
    next.setText("next");
    next.setFontSize(25.f / 720.f * eng->getScreenHeight());
    
    float modelFontSize = 32.f / 720.f * eng->getScreenHeight();
    float menuCenterX = eng->getScreenWidth() * 0.75f * 0.5f + eng->getScreenWidth() * 0.25f;
    float menuCenterY = eng->getScreenHeight() * 0.08f + size.y + 2 + ((eng->getScreenHeight() - modelFontSize - 1) - (eng->getScreenHeight() * 0.08f + size.y + 2) * 0.5f);


    Rectangle pos = {menuCenterX, eng->getScreenHeight() * 0.79f, 100, 50};
    pos.width = 100.f / 720.f * eng->getScreenHeight();
    pos.height = 50.f / 720.f * eng->getScreenHeight();
    pos.x -= pos.width * 0.5f;
    pos.y -= pos.height * 0.5f;
    next.setPosition(pos);
}
