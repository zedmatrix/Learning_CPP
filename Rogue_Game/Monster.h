#ifndef MONSTER_H
#define MONSTER_H

class Monster {

public:
    Monster(std::string name, char tile, int level, int health, int attack, int defense, int xp);
    void setPosition(int x, int y);
    void getPosition(int &x, int &y);
    std::string getName() { return _name; }
    char getTile() { return _tile; }
    void printMonsterStats();
    int attack();
    int takeDamage(int attack);

    char getMove(int playerX, int playerY);

private:

    std::string _name;
    char _tile;
    //Properties
    int _level;
    int _health;
    int _attack;
    int _defense;
    int _experience;

    //Position
    int _x;
    int _y;

};

#endif //MONSTER_H
