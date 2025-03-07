#include "GameSystem.h"

GameSystem::GameSystem() {

}

GameSystem::~GameSystem() {

}

void GameSystem::init() {

    window.init("Main Window Demo", 640, 480);

    mainText.init(20);

    window.drawRect(10, 10, 200, 200, "462f00");

    //mainText.init();
    SDL_Color white = {255, 255, 255, 255};

    int rowX, rowY;
    int x = 20;
    int y = 20;

    std::string _number;
    // Let's Create 9 x 9 boxes
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            rowX = x + i * 20;
            rowY = y + j * 20;
            window.drawBox(rowX, rowY, rowX + 20, rowY + 20);
            window.drawRect(rowX + 1, rowY + 1, 18, 18, "9c6800");
            _number = std::to_string(i + 1);
            mainText.drawText(window.getRenderer(), _number, rowX + 2, rowY + 2, white);
        }
    }

    // Large 3x3 boxes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rowX = x + i * 60;
            rowY = y + j * 60;
            window.drawBox(rowX, rowY, rowX + 60, rowY + 60);
        }
    }

    mainText.drawText(window.getRenderer(), "Hello, SDL!", 300, 300, white);
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
