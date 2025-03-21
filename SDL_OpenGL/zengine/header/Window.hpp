#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "Manager.hpp"

enum WindowFlags { INVISIBLE = 0x1, MAXIMIZED = 0x2, FULLSCREEN = 0x4, BORDERLESS = 0x8 };

class Window {

public:
    Window();
    ~Window();

    int create(std::string windowTitle, int screenWidth, int screenHeight, unsigned int windowFlags);
    void swapBuffer();
    int getScreenWidth() { return _screenWidth; };
    int getScreenHeight() { return _screenHeight; };

private:

    SDL_Window* _sdlWindow;
    int _screenWidth;
    int _screenHeight;
};

#endif //WINDOW_HPP
