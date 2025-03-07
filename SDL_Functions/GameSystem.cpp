#include "GameSystem.h"

GameSystem::GameSystem() {

}

GameSystem::~GameSystem() {

}

void GameSystem::init() {

    window.init("Main Window Demo", 640, 480);

    window.drawBox(50, 50, 100, 100);

    window.drawBox(60, 60, 110, 110, "FF11FF");

    window.drawBox(70, 70, 120, 120, "11EE22");

    window.drawRect(200, 200, 100, 100, "AA5544");

    window.drawRect(300, 300, 100, 100);

    window.present();

    bool running = true;

    while (running) {
        SDL_Event events;
        if (SDL_WaitEvent(&events)) {
            if (events.type == SDL_QUIT) {
                running = false;
            }
        }
    }
}
