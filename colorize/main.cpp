#include <iostream>
#include "colorize.h"

using std::cout;
using std::endl;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    std::string alice = "Alice";
    std::string test = "This is a Test\n";

    std::string hello = colorize("Hello, {}!\n", Colors::RED, true, true, alice);

    print("{} {}", hello, test);
    cout << "Done" << endl;
    return 0;
}
