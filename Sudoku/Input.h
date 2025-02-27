#ifndef INPUT_H
#define INPUT_H

class Input {

public:
    Input();
    int getXCoord();
    int getYCoord();
    int getNumber();

private:
    void print(std::string text);
};

#endif //INPUT_H
