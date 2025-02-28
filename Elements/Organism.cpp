#include "Organism.h"
#include <iostream>
#include <format>

Organism::Organism(const std::string& name) : _name(name) {}

void Organism::addMolecule(const Molecules& molecule) {
    _molecules.push_back(molecule);
}

void Organism::printOrganism() const {
    std::cout << std::format("Organism: {}\n", _name);
    for (const auto& molecule : _molecules) {
        molecule.printMolecule();
    }
}
