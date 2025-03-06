#include <random>
#include <ctime>
#include <format>
#include <iostream>
#include "Monster.h"

Monster::Monster(std::string name, char tile, int level, int health, int attack, int defense, int xp) {

    _name = name;
    _tile = tile;
    _level = level;
    _health = health;
    _attack = attack;
    _defense = defense;
    _experience = xp;

}
void Monster::printMonsterStats() {
    std::cout << std::format("Monster {} Level: {} | Health: {} | Attack: {} | Defense: {} | Experience: {}\n",_name ,_level, _health, _attack, _defense, _experience);
}

void Monster::setPosition(int x, int y) {
    _x = x;
    _y = y;
}

void Monster::getPosition(int &x, int &y) {
    x = _x;
    y = _y;
}

int Monster::attack() {
    static std::default_random_engine randomEngine(time(NULL));
    std::uniform_int_distribution<int> attackRoll(0, _attack);
    return attackRoll(randomEngine);

}

int Monster::takeDamage(int attack) {
    attack -= _defense;
    if (attack > 0) {
        _health -= attack;
        if (_health <= 0) {
            return _experience;
        }
    }
    return 0;
}

char Monster::getMove(int playerX, int playerY) {

    static std::default_random_engine randomEngine(time(NULL));
    std::uniform_int_distribution<int> moveRoll(0, 8);
    int dx = _x - playerX;
    int dy = _y - playerY;
    int adx = std::abs(dx);
    int ady = std::abs(dy);

    int distance = adx + ady;

    if (distance <= 6) {
        if (adx > ady) {
            if (dx > 0) {
                return 'a';
            } else {
                return 's';
            }
        } else {
            if (dy > 0) {
                return 'w';
            } else {
                return 'z';
            }
        }
    }
    int randomMove = moveRoll(randomEngine);
    switch (randomMove) {
        case 0:
        case 8:
            return 'w';
        case 1:
        case 7:
            return 'z';
        case 2:
        case 6:
            return 'a';
        case 3:
        case 5:
            return 's';
        default:
            return '.';
    }
}



