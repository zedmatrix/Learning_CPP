#include <iostream>
#include <istream>
#include <string>
#include <format>
#include <array>
#include <ranges>

// Tutorial #12 Array For Item Shop
std::string outStars(int numStars) {
    return std::format("{}\n", std::string(numStars, '*'));
}
const int shopItems = 8;
const std::array<std::string, shopItems> shopItemNames{"Nails", "Screws", "Hammers", "Screwdrivers", "Saws", "Drills", "Bolts", "Nuts"};

void printInventory(const std::array<int, shopItems> playerInventory) {
    for (const auto& [i, s] : std::views::enumerate(playerInventory)) {
        if (playerInventory[i] > 0) {
            std::cout << std::format("Item #{} - {} x {}\n", i + 1, shopItemNames[i], playerInventory[i]);
        }
    }
}
void printShopItems() {
    std::cout << outStars(30);
    std::cout << "Welcome to the Item Shop\n";
    for (const auto& [i, s] : std::views::enumerate(shopItemNames)) {
        std::cout << std::format("Item #{} -- {}\n", i + 1, s);
    }
    std::cout << outStars(30);
}

bool buyItems(std::array<int, shopItems>& playerInventory) {
    int input;
    std::cout << std::format("What would you like to buy?\n\tEnter -1 to Quit\n\tEnter Number ({}-{})? ", '1', shopItems);
    std::cin >> input;
    if (input == -1) return true;
    if (input < 1 || input > shopItems) {
        std::cout << "Invalid Item!\n";
        return false;
    }
    playerInventory[input - 1]++;
    return false;
}

int main() {
    int chapter = 12;
    std::string chapter_title = "Array For Item Shop";
    std::cout << std::format("C++ Game Tutorial {} {}\n", chapter, chapter_title);

    std::array<int, shopItems> playerInventory{0, 1, 2, 1, 0, 0 , 1, 2};

    bool isDone = false;
    while (isDone == false) {
        std::cout << outStars(20);
        printShopItems();
        printInventory(playerInventory);
        isDone = buyItems(playerInventory);
    }

    std::cout << outStars(30);

    return 0;
}
