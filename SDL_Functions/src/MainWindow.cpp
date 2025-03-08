#include "MainWindow.h"

// Constructor
MainWindow::MainWindow() {

}

// Destructor to make sure its closed properly
MainWindow::~MainWindow() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_GL_ResetAttributes();
    SDL_Quit();
}

void MainWindow::init(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s \n", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        exit(1);
    }
}
bool MainWindow::HextoRGBA(const std::string& color) {
    // Ensure the color is valid (6 characters for RGB or 8 for RGBA)
    if (color.length() != 6 && color.length() != 8) {
        SDL_Log("Invalid color format: %s", color.c_str());
        return false;
    }

    // Convert hex color to integers
    _red = std::stoi(color.substr(0, 2), nullptr, 16);
    _green = std::stoi(color.substr(2, 2), nullptr, 16);
    _blue = std::stoi(color.substr(4, 2), nullptr, 16);
    _alpha = (color.length() == 8) ? std::stoi(color.substr(6, 2), nullptr, 16) : 255;
    return true;
}

void MainWindow::drawBox(int topX, int topY, int bottomX, int bottomY, const std::string& color) {
    if (!HextoRGBA(color)) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, _red, _green, _blue, _alpha);

    SDL_RenderDrawLine(renderer, topX, topY, bottomX, topY); //top line
    SDL_RenderDrawLine(renderer, bottomX, topY, bottomX, bottomY); //right line
    SDL_RenderDrawLine(renderer, bottomX, bottomY, topX, bottomY); //bottom line
    SDL_RenderDrawLine(renderer, topX, bottomY, topX, topY); //left line
}

void MainWindow::drawRect(int topX, int topY, int width, int height, const std::string& color) {
    if (!HextoRGBA(color)) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, _red, _green, _blue, _alpha);
    SDL_Rect rect{topX, topY, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

void MainWindow::present() {
    SDL_RenderPresent(renderer);
}
