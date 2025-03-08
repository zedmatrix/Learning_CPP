#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class MainWindow {

public:
    MainWindow();
    ~MainWindow();

    void init(const char* title, int width, int height);
    void drawBox(int topX, int topY, int bottomX, int bottomY, const std::string& color = "FFFFFF");
    void drawRect(int topX, int topY, int width, int height, const std::string& color = "777777");
    void present();
    SDL_Renderer* getRenderer() { return renderer; };

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool HextoRGBA(const std::string& color);
    int _red;
    int _green;
    int _blue;
    int _alpha;

};

#endif //MAINWINDOW_H
