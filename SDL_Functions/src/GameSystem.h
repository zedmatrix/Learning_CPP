#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "MainWindow.h"
#include "MainText.h"
#include "Sudoku.h"
#include <sstream>

class GameSystem {

public:
    GameSystem();
    ~GameSystem();
    void init();

private:
    MainWindow window;
    MainText mainText;
    Sudoku _sudoku;
    std::vector<std::vector<int>> sudokuBoard;
    std::string colorToHEX(SDL_Color color);
};

#endif //GAMESYSTEM_H
