#include <iostream>
#include <string>
#include <format>
#include <algorithm>
#include <random>
#include <ctime>
#include "Sudoku.h"

bool SudokuGame::isValidMove(const std::array<std::array<char, 9>, 9>& board, int row, int col, char num) {
    // Check row and column
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 box
    int boxRowStart = (row / 3) * 3;
    int boxColStart = (col / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[boxRowStart + i][boxColStart + j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool SudokuGame::fillBoard(std::array<std::array<char, 9>, 9>& board, int row, int col) {
    if (row == 9) return true;
    if (col == 9) return fillBoard(board, row + 1, 0);
    if (board[row][col] != '.') {
        return fillBoard(board, row, col + 1);
    }
    // Try placing numbers 1 to 9 in a shuffled order
    std::array<char, 9> numbers = {'1','2','3','4','5','6','7','8','9'};
    std::ranges::shuffle(numbers, std::mt19937(std::random_device{}()));

    for (char num : numbers) {
        if (isValidMove(board, row, col, num)) {
            board[row][col] = num;
            if (fillBoard(board, row, col + 1)) {
                return true;
            }
            board[row][col] = '.';
        }
    }

    return false;
}

void SudokuGame::removeCells(std::array<std::array<char, 9>, 9>& gameBoard, int maxPerBlock) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 8);

    for (int blockRow = 0; blockRow < 3; ++blockRow) {
        for (int blockCol = 0; blockCol < 3; ++blockCol) {
            std::vector<std::pair<int, int>> cells;
            for (int row = blockRow * 3; row < (blockRow + 1) * 3; ++row) {
                for (int col = blockCol * 3; col < (blockCol + 1) * 3; ++col) {
                    if (gameBoard[row][col] != '.') {
                        cells.emplace_back(row, col);
                    }
                }
            }
            std::shuffle(cells.begin(), cells.end(), gen);
            int removed = 0;
            while (!cells.empty() && removed < maxPerBlock) {
                auto [r, c] = cells.back();
                cells.pop_back();
                gameBoard[r][c] = '.';
                ++removed;
            }
        }
    }
}
