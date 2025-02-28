#include <iostream>
#include <string>
#include <format>
#include <list>
#include "Organism.h"

// Tutorial #19 Class Elements - Vectors and Lists
std::string outStars(int numStars) {
    return std::format("{}\n", std::string(numStars, '*'));
}

std::string printOut(int number, std::string name, std::string symbol) {
    return std::format("Found: #{} {} ({})\n", number, name, symbol);
}
int main() {
    int chapter = 18;
    std::string chapter_title = "Elements Class";
    std::cout << outStars(40);
    std::cout << std::format("C++ Game Tutorial {} {}\n", chapter, chapter_title);

    // Create some Molecules with Elements
    Molecules water("Water", 18);
    water.addElement("Hydrogen", "H", 1, 2);
    water.addElement("Oxygen", "O", 8, 1);
    //water.printMolecule();

    Molecules salt("Salt", 28);
    salt.addElement("Sodium", "Na", 11, 1);
    salt.addElement("Chlorine", "Cl", 17, 1);
    //salt.printMolecule();

    // Search for an element in the molecule
    Elements foundElement("", "", 0);
    if (water.getElement("Hydrogen", foundElement)) {
        std::cout << printOut(foundElement.getNumber(), foundElement.getName(), foundElement.getSymbol());

    } else {
        std::cout << "Hydrogen not found!" << std::endl;
    }

    if (salt.getElement("Sodium", foundElement)) {
        std::cout << printOut(foundElement.getNumber(), foundElement.getName(), foundElement.getSymbol());
    } else {
        std::cout << "Sodium not found!" << std::endl;
    }
    std::cout << outStars(30);

    // Create an organism composition with Molecules
    Organism Human("Human");
    Human.addMolecule(water);
    Human.addMolecule(salt);
    Human.printOrganism();

    std::cout << outStars(40);

    return 0;
}
