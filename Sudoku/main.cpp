#include <iostream>
#include <string>
#include <format>
#include "Sudoku.h"

// Game Sudoku Classes and Multi-Dimensional Arrays
std::string outStars(int numStars) {
    return std::format("{}\n", std::string(numStars, '*'));
}

int main() {
    int chapter = 16;
    std::string chapter_title = "Multi-Dimensional Arrays - Sudoku Board";
    std::cout << std::format("C++ Game Tutorial {} {}\n", chapter, chapter_title);
    std::cout << outStars(40);

    SudokuGame game;
    game.playGame();

    std::cout << outStars(40);
    return 0;
}
