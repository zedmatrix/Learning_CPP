#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H
#include <unistd.h>
#include <termios.h>
#include <string>
#include "Player.h"
#include "Level.h"

class GameSystem {

public:
    GameSystem(std::string levelFile);

    void playGame();
    void playerMove();
    char getch();

private:
    Level _level;
    Player _player;

};

#endif //GAMESYSTEM_H
