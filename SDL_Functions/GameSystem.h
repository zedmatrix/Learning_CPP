#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "MainWindow.h"

class GameSystem {

public:
    GameSystem();
    ~GameSystem();
    void init();

private:
    MainWindow window;
};

#endif //GAMESYSTEM_H
