#include <iostream>
#include <vector>
#include <string>
#include <format>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class Menu {
private:
    std::vector<std::string> options = { "A", "B", "C", "D", "X" };

public:
    void show() {
        print("Menu Options: (");
        for (size_t i = 0; i < options.size(); ++i) {
            if (i < options.size() - 1) {
                print("{} /", options[i]);
            } else {
                print("{}", options[i]);
            }
        }
        print(")\n");
    }

    char getChoice() {
        char choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        return choice;
    }

    bool processChoice(char choice) {
        auto char_upper = [](char c) {
            if(c >= 'a' && c <= 'z') return static_cast<char>(c - ('a' - 'A'));
            else return c;
        };
        char x = char_upper(choice);
        switch (x) {
            case 'A':
                print("Option {} selected\n", x);
                break;
            case 'B':
                print("Option {} selected\n", x);
                break;
            case 'C':
                print("Option {} selected\n", x);
                break;
            case 'D':
                print("Option {} selected\n", x);
                break;
            case 'X':
                print("Option {} selected\n", x);
                print("Good Bye\n");
                return false;
            default:
                print("Invalid Option {} ,Please Try Again\n", x);
                break;
        }
        return true;
    }
};

int main() {
    Menu menu;
    char choice;
    bool keepRunning = true;

    while (keepRunning) {
        menu.show();
        choice = menu.getChoice();
        keepRunning = menu.processChoice(choice);
    }

    return 0;
}
