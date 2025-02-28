#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <string>

class Elements {

public:
    Elements(std::string name, std::string symbol, int number);

    void addElement();
    void removeElement();

    std::string getName() const { return _name; }
    std::string getSymbol() const { return _symbol; }
    int getNumber() const { return _number; }
    int getCount() const { return _count; }

    Elements& setCount(int count) { _count = count; return *this; }

private:
    std::string _name;
    std::string _symbol;
    int _number;
    int _count;

};


#endif //ELEMENTS_H
