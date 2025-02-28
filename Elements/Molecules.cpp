#include <iostream>
#include <string>
#include <format>
#include "Molecules.h"

Molecules::Molecules(std::string name, int weight) {
    _name = name;
    _weight = weight;
}

void Molecules::printMolecule() const {
    std::cout << outStars(30);
    std::cout << std::format("Molecule Information: {}\n", _name) << outStars(30);

    std::list<Elements>::const_iterator it;

    for (it = _elements.begin(); it != _elements.end(); it++) {
        std::cout << std::format("Element {} Symbol {} is {}\n", (*it).getNumber(),(*it).getSymbol(), (*it).getName());

    }

}
void Molecules::addMolecule(Elements newMolecule) {
    for (auto& element : _elements) {
        if (element.getName() == newMolecule.getName()) {
            element.addElement();
            return;
        }
    }
    _elements.push_back(newMolecule);
}

void Molecules::addElement(const std::string& name, const std::string& symbol, int number, int count) {
    addMolecule(Elements(name, symbol, number).setCount(count));
}

bool Molecules::getElement(std::string name, Elements& newMolecule) {
    for (const auto& element : _elements) {
        if (element.getName() == name) {
            newMolecule = element;
            return true;
        }
    }
    return false;
}
