#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

int main() {
    std::vector<int> left;
    std::vector<int> right;
    std::string line;

    std::ifstream file_in("input.data");
    if (!file_in) { std::cout << "File Error:\n"; return 1; }

    while (std::getline(file_in, line)) {
        std::istringstream iss(line);
        int leftNum, rightNum;

        if (iss >> leftNum >> rightNum) {
            left.push_back(leftNum);
            right.push_back(rightNum);
        } else {
            std::cerr << "Error: Invalid line format: " << line << "\n";
        }
    }
    file_in.close();

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    std::cout << "Left: [";
    for (int i: left)
         std::cout << i << ',';
    std::cout << "]\n";

    std::cout << "Right: [";
    for (int i: right)
        std::cout << i << ',';
    std::cout << "]\n";

    int totalDistance = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        totalDistance += std::abs(left[i] - right[i]);
    }
    std::cout << "Total Distance: " << totalDistance << '\n';
    return 0;
}
