#include "Elements.h"

Elements::Elements(std::string name, std::string symbol, int number) {
    _name = name;
    _symbol = symbol;
    _number = number;
    _count = 1;
}

void Elements::addElement() {
    _count++;
}

void Elements::removeElement() {
    if (_count > 0) {
        _count--;
    }

}

