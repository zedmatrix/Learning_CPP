#include "GameSystem.h"

GameSystem::GameSystem() {

}

GameSystem::~GameSystem() {

}
std::string GameSystem::colorToHEX(SDL_Color color) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(color.r)
       << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(color.g)
       << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(color.b)
       << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(color.a);
    return ss.str();
}
void GameSystem::init() {

    window.init("Main Window Demo", 640, 480);
    mainText.init(20);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color raspberry = {227, 66, 52, 128};
    SDL_Color darkBrown = {70, 47, 0, 255};
    SDL_Color lightBrown = {156, 104, 0, 255};

    window.drawRect(10, 10, 200, 200, colorToHEX(lightBrown)); //gameBoard"462f00"
    window.drawRect(220, 10, 200, 200, colorToHEX(raspberry)); //solutionBoard
    //Generate Sudoku Board

    std::srand(time(0));
    std::vector<std::vector<int>> solutionBoard = _sudoku.sudokuGenerator();
    std::vector<std::vector<int>> gameBoard = solutionBoard;
    _sudoku.removeKDigits(gameBoard, 20);
    int rowX, rowY;
    int x = 20;
    int y = 20;
    std::string _number;
    // Let's Create 9 x 9 boxes  gameBoard
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            rowX = x + i * 20;
            rowY = y + j * 20;
            window.drawBox(rowX, rowY, rowX + 20, rowY + 20);
            window.drawRect(rowX + 1, rowY + 1, 18, 18, colorToHEX(darkBrown));
            _number = std::to_string(gameBoard[i][j]);
            if (std::stoi(_number) > 0) mainText.drawText(window.getRenderer(), _number, rowX + 3, rowY, white);
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

    // Let's Create 9 x 9 boxes  solutionBoard
    x = 230;
    y = 20;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            rowX = x + i * 20;
            rowY = y + j * 20;
            window.drawBox(rowX, rowY, rowX + 20, rowY + 20);
            window.drawRect(rowX + 1, rowY + 1, 18, 18, colorToHEX(darkBrown)); //"9c6800"
            _number = std::to_string(solutionBoard[i][j]);
            mainText.drawText(window.getRenderer(), _number, rowX + 3, rowY, white);
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

    mainText.drawText(window.getRenderer(), "Hello, SDL!", 300, 300, raspberry);
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
