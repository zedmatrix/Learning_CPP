#include <iostream>
#include <format>
#include <string>
#include "TicTacToeGame.h"

std::string outStars(int numStars) {
    return std::format("{}\n", std::string(numStars, '*'));
}

int main() {
    std::string mainTitle = "Game Challenge";
    int mainChapter = 2;
    std::cout << outStars(40);
    std::cout << std::format("\t{} #{}\n", mainTitle, mainChapter);

    bool isDone = false;
    char input;
    TicTacToeGame game;
    while (isDone == false) {
        game.playGame();
        std::cout << "Would You Like to Play Again? (Y/N)";
        std::cin >> input;
        if (input == 'N' || input == 'n') {
            isDone = true;
        }
    }

    std::cout << outStars(40);
    return 0;
}
