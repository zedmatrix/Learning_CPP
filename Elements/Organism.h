#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>
#include <vector>
#include "Molecules.h"

class Organism {
public:
    Organism(const std::string& name);

    void addMolecule(const Molecules& molecule);
    void printOrganism() const;

private:
    std::string _name;
    std::vector<Molecules> _molecules;
};

#endif // ORGANISM_H
