#include "GameSystem.h"


GameSystem::GameSystem(std::string levelFile) {
    //int level, int health, int attack, int defense, int experience
    _player.init(1, 100, 20, 20, 20);
    _level.load(levelFile, _player);

}

void GameSystem::playGame() {

    bool isDone = false;

    //game loop
    while (isDone != true) {
        _level.print();
        _player.printPlayerStats();
        playerMove();
        _level.updateMonsters(_player);

    }
}
// Function to get a character without Enter key
char GameSystem::getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void GameSystem::playerMove() {
    char input;
    std::printf("Enter a move command (q = quit or Move = w/a/s/z): \n");
    input = getch();

    _level.movePlayer(input, _player);

}
