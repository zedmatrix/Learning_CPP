#include <iostream>
#include <format>
#include <string>
#include "GameSystem.h"

std::string outStars(int numStars) {
    return std::format("{}\n", std::string(numStars, '*'));
}

int main() {
    int chapter = 1;
    std::string chapter_title = "Class, Objects and SDL Windows";
    std::cout << std::format("C++ Game Tutorial {} {}\n", chapter, chapter_title);
    std::cout << outStars(40);

    GameSystem game;
    game.init();

    return 0;
}
