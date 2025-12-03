#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
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

    int delta {};
    int similar {};
    for (int i: left) {
        delta = 0;
        std::cout << "Checking:" << i << '\n';
        for (int j: right) {
            if (i == j) delta++;

        }
        similar += i * delta;
    }

    std::cout << "Total Similarity: " << similar << '\n';
    return 0;
}
