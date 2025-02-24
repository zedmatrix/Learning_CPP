#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <format>

int getInput(std::string text) {
    int input;
    std::cout << std::format("{}: ", text);
    std::cin >> input;
    if (input < 10) {
        input = 10;
    }
    return input;
}
void printSummary(int startHumans, int numberHumans, int startZombies, int numberZombies) {
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

}
void simulateBattle(const float health, int numberHumans, int numberZombies) {
    int startHumans = numberHumans;
    int startZombies = numberZombies;
    std::default_random_engine randomGen(time(0));
    std::uniform_real_distribution<float> attackRoll(0.0f, 1.0f);
    float zombie_health = health;
    float human_health = health;
    float attack;
    std::cout << std::format("Starting Combat: {} Humans With Hit Points: {}\n", numberHumans, human_health);
    std::cout << std::format("Starting Combat: {} Zombies With Hit Points: {}\n", numberZombies, zombie_health);
    char turn = 'H';

    while (numberHumans > 0 && numberZombies > 0) {
        zombie_health = health;
        human_health = health;
        std::cout << std::format("\tHumans: {}\t Zombies: {}\n", numberHumans, numberZombies);
        while (human_health > 0.0f && zombie_health > 0.0f) {
            attack = attackRoll(randomGen);

            if (turn == 'H') {
                zombie_health -= attack;
                //std::cout << std::format("Human Attack: {:.2f}  Zombie Health: {:.2f} \n", attack, zombie_health);
                turn = 'Z';
            } else {
                human_health -= attack;
                //std::cout << std::format("Zombie Attack: {:.2f}  Human Health: {:.2f} \n", attack, human_health);
                turn = 'H';
            }
        }
        if (human_health < 0.0f) {
            numberHumans--;
        } else {
            numberZombies--;
        }

    }
    printSummary(startHumans, numberHumans, startZombies, numberZombies);
}

//Game Challenge: 1 - Humans vs Zombies
int main() {
    std::cout << "Welcome to Humans vs Zombies\n" << "\t\tCombat Simulator\n";

    const float health = 100.0f;
    int numberHumans;
    int numberZombies;

    numberHumans = getInput("Input Number of Humans");
    numberZombies = getInput("Input Number of Zombies");

    // Humans vs Zombies
    simulateBattle(health, numberHumans, numberZombies);

    return 0;
}
