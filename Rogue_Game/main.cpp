#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <cstdio>
#include <cstdlib>
#include <chrono>   //for time wait
#include <thread>
#include "GameSystem.h"

std::string outChar(long unsigned int x, char c) {
    return std::format("\n\t{}\n", std::string(x, c));
}

std::string CLEAR_SCREEN() { return "\033[2J\033[H"; }

int main() {
    int chapter = 25;
    std::string chapter_title = "ASCII Rogue Like";
    std::cout << std::format("C++ Game Tutorial {} {}\n", chapter, chapter_title);
    std::cout << outChar(40, '*');
    std::printf("Initializing the Game!\n");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << CLEAR_SCREEN();

    GameSystem gameSystem("level1.txt");
    gameSystem.playGame();

    std::cout << outChar(40, '=');
    return 0;
}
