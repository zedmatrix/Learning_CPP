#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <format>

//Game Challenge: 1 - Humans vs Zombies
int main() {
    std::cout << "Welcome to Humans vs Zombies\n" << "\t\tCombat Simulator\n";
    std::default_random_engine randomGen(time(0));

    int i = 1;
    int roll = 10;
    const float health = 100.0f;

    int numberHumans;
    float human_damage = 0.0f;
    float human_health = health;
    float human_attack = 0.0f;

    int numberZombies;
    float zombie_damage = 0.0f;
    float zombie_health = health;
    float zombie_attack = 0.0f;

    std::cout << "Input Number of Humans: ";
    std::cin >> numberHumans;
    if (numberHumans < 1) {
        numberHumans = 1;
    }
    int startHumans = numberHumans;

    std::cout << "Input Number of Zombies: ";
    std::cin >> numberZombies;
    if (numberZombies < 1) {
        numberZombies = 1;
    }
    int startZombies = numberZombies;

    // Humans vs Zombies
    std::uniform_real_distribution<float> attackRoll(0.0f, 1.0f);

    do {
        zombie_health = health;
        human_health = health;
        std::cout << std::format("Starting Combat: {} Humans With Hit Points: {}\n", numberHumans, human_health);
        std::cout << std::format("Starting Combat: {} Zombies With Hit Points: {}\n", numberZombies, zombie_health);
        // TODO: wait between combats

        //Human Health vs Zombie Health
        while (human_health > 0.0f && zombie_health > 0.0f) {
            i = 1;
            while (i < roll) {
                human_attack = attackRoll(randomGen);
                zombie_damage = attackRoll(randomGen);
                if (human_attack < zombie_damage) zombie_damage = human_attack;
                std::cout << std::format("Human Attacking with {:.4f} producing {:.4f} damage\n", human_attack, zombie_damage);
                zombie_health -= zombie_damage;
                i++;
            }

            i = 1;
            while (i < roll) {
                zombie_attack = attackRoll(randomGen);
                human_damage = attackRoll(randomGen);
                if (zombie_attack < human_damage) human_damage = zombie_attack;
                std::cout << std::format("Zombie Attacking with {:.4f} producing {:.4f} damage\n", zombie_attack, human_damage);
                human_health -= human_damage;
                i++;
            }
            std::cout << std::format("Statistics Human Health: {:.2f} Zombie Health: {:.2f}\n", human_health, zombie_health);

        }

        if (human_health < 0.0f) {
            numberHumans--;
            std::cout << std::format("Humans {} Lost\n", numberHumans);
        } else {
            numberZombies--;
            std::cout << std::format("Zombies {} Lost\n", numberZombies);
        }
    } while (numberHumans > 0 && numberZombies > 0);

    if (numberHumans > numberZombies) {
        std::cout << std::format("Humans Win: {}/{} ,Zombies killed: {}, Humans Killed: {}\n",
                                 numberHumans,
                                 startHumans,
                                 startZombies,
                                 startHumans - numberHumans);
    } else {
        std::cout << std::format("Zombies Win: {}/{} ,Humans Killed: {}, Zombies Killed: {}\n",
                                 numberZombies,
                                 startZombies,
                                 startHumans,
                                 startZombies - numberZombies);
    }

    return 0;
}

