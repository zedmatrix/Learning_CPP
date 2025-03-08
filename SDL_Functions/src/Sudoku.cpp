#include "Sudoku.h"

Sudoku::Sudoku() {

}

Sudoku::~Sudoku() {

}
// Public Function to Generate Puzzle Board
std::vector<std::vector<int>> Sudoku::sudokuGenerator() {

    std::vector<std::vector<int>> grid(9, std::vector<int>(9, 0));
    fillDiagonal(grid);
    fillRemaining(grid, 0, 0);

    return grid;
}
void Sudoku::removeKDigits(std::vector<std::vector<int>> &grid, int k) {
    while (k > 0) {
        int cellId = rand() % 81;
        int i = cellId / 9;
        int j = cellId % 9;
        if (grid[i][j] != 0) {
            grid[i][j] = 0;
            k--;
        }
    }
}
// Private Functions
bool Sudoku::unUsedInBox(std::vector<std::vector<int>> &grid, int rowStart, int colStart, int num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[rowStart + i][colStart + j] == num) {
                return false;
            }
        }
    }
    return true;
}
// Fill a 3x3 matrix and Assign valid random numbers to the 3x3 subgrid
void Sudoku::fillBox(std::vector<std::vector<int>> &grid, int row, int col) {
    int num;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            do {
                num = (std::rand() % 9) + 1;
            } while (!unUsedInBox(grid, row, col, num));
            grid[row + i][col + j] = num;
        }
    }
}
// Check if it's safe to put num in row i and Ensure num is not already used in the row
bool Sudoku::unUsedInRow(std::vector<std::vector<int>> &grid, int i, int num) {
    for (int j = 0; j < 9; j++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}
bool Sudoku::unUsedInCol(std::vector<std::vector<int>> &grid, int j, int num) {
    for (int i = 0; i < 9; i++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}
bool Sudoku::checkIfSafe(std::vector<std::vector<int>> &grid, int i, int j, int num) {
    return (unUsedInRow(grid, i, num) && unUsedInCol(grid, j, num) &&
            unUsedInBox(grid, i - i % 3, j - j % 3, num));
}
void Sudoku::fillDiagonal(std::vector<std::vector<int>> &grid) {
    for (int i = 0; i < 9; i = i + 3) {
        fillBox(grid, i, i);
    }
}
bool Sudoku::fillRemaining(std::vector<std::vector<int>> &grid, int i, int j) {
    if (i == 9) {
        return true;
    }
    if (j == 9) {
        return fillRemaining(grid, i + 1, 0);
    }
    if (grid[i][j] != 0) {
        return fillRemaining(grid, i, j + 1);
    }
    for (int num = 1; num <= 9; num++) {
        if (checkIfSafe(grid, i, j, num)) {
            grid[i][j] = num;
            if (fillRemaining(grid, i, j + 1)) {
                return true;
            }
            grid[i][j] = 0;
        }
    }

    return false;
}
