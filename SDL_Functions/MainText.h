#ifndef MAINTEXT_H
#define MAINTEXT_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include "MainWindow.h"

class MainText {

public:
    MainText();
    ~MainText();
    void init(int fontSize);
    void drawText(SDL_Renderer* renderer, std::string text, int x, int y, SDL_Color color);

private:
    TTF_Font* font = nullptr;

};

#endif //MAINTEXT_H
