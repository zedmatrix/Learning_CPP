#include <iostream>
#include "Input.h"

Input::Input() {
}

int Input::getXCoord() {
    int x;
    print("Enter X Coordinate: ");
    std::cin >> x;
    if (x > 0 && x < 10) {
        return x;
    } else {
        print("Invalid X Coordinate!");
        return 0;
    }
    return 0;

}

int Input::getYCoord() {
    int y;
    print("Enter y Coordinate: ");
    std::cin >> y;
    if (y > 0 && y < 10) {
        return y;
    } else {
        print("Invalid Y Coordinate!");
        return 0;
    }
    return 0;

}

int Input::getNumber() {
    int n;
    print("Enter Number For Coordinate:");
    std::cin >> n;
    if (n > 0 && n < 10) {
        return n;
    } else {
        print("Invalid Number!");
        return 0;
    }
    return 0;
}

void Input::print(std::string text) {
    std::cout << text << ' ';
}
