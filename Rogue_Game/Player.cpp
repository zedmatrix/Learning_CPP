#include <random>
#include <ctime>
#include <chrono>   //for time wait
#include <thread>
#include <format>
#include <iostream>
#include "Player.h"

Player::Player() {
    _x = 0;
    _y = 0;
}

void Player::init(int level, int health, int attack, int defense, int experience) {
    _level = level;
    _health = health;
    _attack = attack;
    _defense = defense;
    _experience = experience;
}

void Player::setPosition(int x, int y) {
    _x = x;
    _y = y;
}
void Player::addExperience(int experience) {
    _experience += experience;

    //Level up
    while (_experience > 50) {
        std::printf("Levelled Up\n");
        _experience -= 50;
        _attack += 10;
        _defense += 10;
        _health += 10;
        _level++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Player::getPosition(int &x, int &y) {
    x = _x;
    y = _y;
}

int Player::attack() {
    static std::default_random_engine randomEngine(time(NULL));
    std::uniform_int_distribution<int> attackRoll(0, _attack);
    return attackRoll(randomEngine);

}

int Player::takeDamage(int attack) {
    attack -= _defense;
    if (attack > 0) {
        _health -= attack;
        if (_health <= 0) {
            return 1;
        }
    }
    return 0;
}

void Player::printPlayerStats() {
    std::cout << std::format("Player Level: {} | Health: {} | Attack: {} | Defense: {} | Experience: {}\n",_level, _health, _attack, _defense, _experience);
}
