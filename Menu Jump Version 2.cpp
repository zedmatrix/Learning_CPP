#include <format>
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <map>
using std::string;
using std::vector;
using namespace std;


// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}
void disp_v(const auto& v) {
    print("Menu Options: ({}/{}/{}/{}/{})", v[0], v[1], v[2], v[3], v[4]);
    print("\n");
}
class Option {
    char opt {};
    std::map<char, std::function<void(char&)>> menu_map;  // Map to associate chars with functions

public:
    Option(char x = 'X') : opt(x) {
        // Initialize the map with function bindings
        menu_map['A'] = [this](char& c) { Func_A(c); };
        menu_map['B'] = [this](char& c) { Func_B(c); };
        menu_map['C'] = [this](char& c) { Func_C(c); };
        menu_map['D'] = [this](char& c) { Func_D(c); };
    }
    // Define the functions
    void Func_A(char& c) {
        print("Function {} called\n", c);
    }

    void Func_B(char& c) {
        print("Function {} called\n", c);
    }

    void Func_C(char& c) {
        print("Function {} called\n", c);
    }

    void Func_D(char& c) {
        print("Function {} called\n", c);
    }
    // Method to execute the function associated with a character
    void execute(char c) {
        auto it = menu_map.find(c);
        if (it != menu_map.end()) {
            it->second(c);  // Call the function associated with the character
        } else {
            print("** Invalid option **\n");
        }
    }
};

int main() {
    bool keepRunning = true;
    char choice;
    const char* stars = "*****";
    const char* start = "Jump Challenge";
    auto title = [start]() { return start; };
    auto s = [stars]() { return stars; };

    print("{} {} {}\n", s(), title(), s());

    // Convert entire string to uppercase
    auto char_upper = [](char c) {
        if(c >= 'a' && c <= 'z') return static_cast<char>(c - ('a' - 'A'));
        else return c;
    };
    vector<string> options = { "A", "B", "C", "D", "X"};
    string option;

    Option opt;
    char a;
    while (keepRunning) {
        disp_v(options);
        cin >> option;
        a = char_upper(option[0]);
        if (option.length() > 1) {
            print("Response of {} ,Too Long\n", option);
            keepRunning = true;
        } else if (a == 'X') {
            print("{} Good Bye {}\n\n", s(), a);
            keepRunning = false;
        } else {
            opt.execute(a);
        }
    }

    return 0;
}
