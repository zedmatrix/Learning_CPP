#include <fstream>
#include <iostream>
#include <chrono>   //for time wait
#include <thread>
#include "Level.h"

Level::Level() {

}

void Level::load(std::string fileName, Player &player) {
    // Load Level
    std::ifstream file;

    file.open(fileName);

    if (file.fail()) {
        std::perror(fileName.c_str());
        exit(1);
    }
    std::string line;
    while (std::getline(file, line)) {
        _levelData.push_back(line);
    }
    file.close();

    //Process Level
    char tile;
    for (std::size_t i = 0; i < _levelData.size(); i++) {
        for (std::size_t j = 0; j < _levelData[i].size(); j++) {
            tile = _levelData[i][j];

            //std::string name, char tile, int level, int health, int attack, int defense, int xp
            switch (tile) {
                case '@':   //Player
                    player.setPosition(j,i);
                    break;
                case 'S':   //Snake
                    _monsters.push_back(Monster("Snake", tile, 1, 3, 1, 10, 50));
                    _monsters.back().setPosition(j, i);
                    break;
                case 'G':   //Goblin
                    _monsters.push_back(Monster("Goblin", tile, 2, 10, 5, 10, 50));
                    _monsters.back().setPosition(j, i);
                    break;
                case 'B':   //Bandit
                    _monsters.push_back(Monster("Bandit", tile, 3, 20, 10, 5, 50));
                    _monsters.back().setPosition(j, i);
                    break;
                case 'O':   //Ogre
                    _monsters.push_back(Monster("Ogre", tile, 4, 30, 15, 15, 100));
                    _monsters.back().setPosition(j, i);
                    break;
                case 'D':   //Dragon
                    _monsters.push_back(Monster("Dragon", tile, 5, 100, 100, 100, 100));
                    _monsters.back().setPosition(j, i);
                    break;

            }
        }
    }

}

void Level::print() {
    std::cout << CLEAR_SCREEN();

    for (std::size_t i = 0; i < _levelData.size(); i++) {
        std::printf("%s\n", _levelData[i].c_str());
    }
    std::printf("\n");
}
void Level::battleMonster(Player &player, int targetX, int targetY) {

    int monsterX;
    int monsterY;
    int playerX;
    int playerY;
    int attackRoll;
    int attackResult;
    std::string monsterName;

    player.getPosition(playerX, playerY);
    for (std::size_t i = 0; i < _monsters.size(); i++) {
        _monsters[i].getPosition(monsterX, monsterY);
        monsterName = _monsters[i].getName();

        if (targetX == monsterX && targetY == monsterY) {
            //Battle Monster

            attackRoll = player.attack();
            std::printf("Player attacking %s with %d\n", monsterName.c_str(), attackRoll);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            attackResult = _monsters[i].takeDamage(attackRoll);
            if (attackResult != 0) {
                setTile(targetX, targetY, '.');
                print();
                std::printf("Monster died!\n");
                _monsters[i] = _monsters.back();
                _monsters.pop_back();
                i--;
                player.addExperience(attackResult);
                std::this_thread::sleep_for(std::chrono::seconds(1));

                return;
            }
            // Monster fights

            attackRoll = _monsters[i].attack();
            std::printf("%s attacking Player with %d\n", monsterName.c_str(), attackRoll);
            attackResult = player.takeDamage(attackRoll);
            if (attackResult != 0) {
                setTile(playerX, playerY, 'x');
                print();
                std::printf("You died!\n");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                exit(0);
                return;
            }

            _monsters[i].printMonsterStats();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
    }
}

void Level::processMove(Player &player, int targetX, int targetY) {
    int playerX;
    int playerY;
    player.getPosition(playerX, playerY);
    char moveTile = getTile(targetX, targetY);

    switch (moveTile) {
        case '#':
            std::printf("You Ran into a Wall\n");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        case '.':
            player.setPosition(targetX, targetY);
            setTile(playerX, playerY, '.');
            setTile(targetX, targetY, '@');
            break;
        default:
            battleMonster(player, targetX, targetY);
            break;
    }
}
void Level::moveMonster(Player &player, int monsterIndex, int targetX, int targetY) {
    int playerX;
    int playerY;
    player.getPosition(playerX, playerY);

    int monsterX;
    int monsterY;
    _monsters[monsterIndex].getPosition(monsterX, monsterY);

    char moveTile = getTile(targetX, targetY);

    switch (moveTile) {
        case '.':
            _monsters[monsterIndex].setPosition(targetX, targetY);
            setTile(monsterX, monsterY, '.');
            setTile(targetX, targetY, _monsters[monsterIndex].getTile());
            break;

        case '@':
            battleMonster(player, monsterX, monsterY);
            break;
        default:

            break;
    }
}

void Level::updateMonsters(Player &player) {
    char aiMove;
    int playerX;
    int playerY;
    player.getPosition(playerX, playerY);
    int monsterX;
    int monsterY;


    for (std::size_t i = 0; i < _monsters.size(); i++) {
        aiMove = _monsters[i].getMove(playerX, playerY);
        _monsters[i].getPosition(monsterX, monsterY);

        switch (aiMove) {
            case 'w': //Up
            moveMonster(player, i, monsterX, monsterY - 1);
            break;
        case 'a': //Left
            moveMonster(player, i, monsterX - 1, monsterY);
            break;
        case 's': //Right
            moveMonster(player, i, monsterX + 1, monsterY);
            break;
        case 'z': //Down
            moveMonster(player, i, monsterX, monsterY + 1);
            break;
        }
    }
}

void Level::movePlayer(char input, Player &player) {
    int playerX;
    int playerY;
    player.getPosition(playerX, playerY);

    switch (input) {
        case 'w': //Up
        case 'W':
            processMove(player, playerX, playerY - 1);
            break;

        case 'a': //Left
        case 'A':
            processMove(player, playerX - 1, playerY);
            break;

        case 's': //Right
        case 'S':
            processMove(player, playerX + 1, playerY);
            break;

        case 'z': //Down
        case 'Z':
            processMove(player, playerX, playerY + 1);
            break;

        case 'q': //Quit
        case 'Q':
            std::printf("Good Bye!\n");
            exit(0);
            break;
        default:
            std::printf("Invalid Input!\n");
            break;
    }

}
void Level::setTile(int x, int y, char tile) {
    _levelData[y][x] = tile;
}

char Level::getTile(int x, int y) {
    return _levelData[y][x];
}
