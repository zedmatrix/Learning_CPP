#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include "Player.h"
#include "Monster.h"

class Level {

public:
    Level();
    void load(std::string fileName, Player &player);
    void print();
    void movePlayer(char input, Player &player);
    void updateMonsters(Player &player);
    char getTile(int x, int y);
    void setTile(int x, int y, char tile);

private:
    std::vector<std::string> _levelData;
    std::vector<Monster> _monsters;
    std::string CLEAR_SCREEN() { return "\033c\033[2J\033[H"; }
    void processMove(Player &player, int targetX, int targetY);
    void moveMonster(Player &player, int monsterIndex, int targetX, int targetY);
    void battleMonster(Player &player, int targetX, int targetY);

};

#endif //LEVEL_H
