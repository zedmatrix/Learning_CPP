#include <iostream>
#include "colorize.h"

using std::cout;
using std::endl;

int main() {
    std::string test = "test";
    int x = 5;
    cout << colorize("Hello, World! {}", Colors::RED, true, true, x) << endl;
    cout << colorize("This is a {}.", Colors::GREEN, false, false, test) << endl;
    return 0;
}
