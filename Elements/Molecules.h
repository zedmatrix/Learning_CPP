#ifndef MOLECULES_H
#define MOLECULES_H

#include <string>
#include <list>
#include <format>
#include "Elements.h"

class Molecules {

public:
    Molecules(std::string name, int _weight);
    void printMolecule() const;
    void addMolecule(Elements newMolecule);
    bool getElement(std::string name, Elements& newMolecule);
    void addElement(const std::string& name, const std::string& symbol, int number, int count);


private:
    std::string _name;
    std::list<Elements> _elements;
    int _weight;
    std::string outStars(int numStars) const { return std::format("{}\n", std::string(numStars, '*')); }

};

#endif //MOLECULES_H
