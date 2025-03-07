#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "MainWindow.h"
#include "MainText.h"

class GameSystem {

public:
    GameSystem();
    ~GameSystem();
    void init();

private:
    MainWindow window;
    MainText mainText;
};

#endif //GAMESYSTEM_H
