#include "MainText.h"

MainText::MainText() {}

MainText::~MainText() {
    if (font) TTF_CloseFont(font);
    TTF_Quit();
}

void MainText::init(int fontSize) {
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }
    font = TTF_OpenFont("fonts/timesbd.ttf", fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

void MainText::drawText(SDL_Renderer* renderer, std::string text, int x, int y, SDL_Color color) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Text render error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Texture creation error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);

}
