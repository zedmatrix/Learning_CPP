#include <iostream>
#include <string>
#include <format>
#include <algorithm>
#include <random>
#include <ctime>
#include "Sudoku.h"

SudokuGame::SudokuGame() {

}
void SudokuGame::playGame() {
    std::cout << "Initializing Board" << std::endl;
    initBoard();

    std::cout << "Solution Board:\n" << std::endl;
    printBoard(board);

    std::array<std::array<char, 9>, 9> gameBoard = board;
    //removeCells(gameBoard, 40); generic per board
    removeCells(gameBoard, 4); // per block removal

    std::cout << "Game Board:\n" << std::endl;
    printBoard(gameBoard);

    //TODO: gameLoop

}

void SudokuGame::initBoard() {
    std::srand(std::time(nullptr));
    for (auto& row : board) {
        row.fill('.');
    }
    if (!fillBoard(board)) {
        std::cerr << "Error: Failed to generate a valid Sudoku board." << std::endl;
    }

    shuffleBoard();

}

void SudokuGame::shuffleBoard() {
    // Shuffle rows within each band (0-2, 3-5, 6-8)
    for (int band = 0; band < 3; ++band) {
        std::array<int, 3> rowIndices = {0, 1, 2};
        std::ranges::shuffle(rowIndices, std::mt19937(std::random_device{}()));

        std::array<std::array<char, 9>, 3> temp;
        for (int i = 0; i < 3; ++i) {
            temp[i] = board[band * 3 + rowIndices[i]];
        }
        for (int i = 0; i < 3; ++i) {
            board[band * 3 + i] = temp[i];
        }
    }

    // Shuffle columns within each stack
    for (int stack = 0; stack < 3; ++stack) {
        std::array<int, 3> colIndices = {0, 1, 2};
        std::ranges::shuffle(colIndices, std::mt19937(std::random_device{}()));

        for (int row = 0; row < 9; ++row) {
            std::array<char, 3> temp;
            for (int i = 0; i < 3; ++i) {
                temp[i] = board[row][stack * 3 + colIndices[i]];
            }
            for (int i = 0; i < 3; ++i) {
                board[row][stack * 3 + i] = temp[i];
            }
        }
    }
}

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

// void SudokuGame::removeCells(std::array<std::array<char, 9>, 9>& gameBoard, int cellsToRemove) {
//     int removed = 0;
//     while (removed < cellsToRemove) {
//         int row = std::rand() % 9;
//         int col = std::rand() % 9;
//
//         if (gameBoard[row][col] != '.') {
//             gameBoard[row][col] = '.';
//             ++removed;
//         }
//     }
// }

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

void SudokuGame::printBoard(const std::array<std::array<char, 9>, 9>& board) {
    std::cout << "\t X   |";
    for (int i = 0; i < 9; ++i) {
        std::cout << std::format(" {}{}", i + 1, (i % 3 == 2) ? " ||" : " |");
    }
    std::cout << "\n\t" << std::string(45, '-') << "\n";

    for (int row = 0; row < 9; ++row) {
        if (row % 3 == 0 && row != 0) {
            std::cout << '\t' << std::string(45, '-') << "\n";
        }

        std::cout << "\t Y " << (row + 1) << " |";
        for (int col = 0; col < 9; ++col) {
            std::cout << " " << board[row][col] << " |";

            // Add double bar after each 3x3 block (excluding the last column)
            if ((col + 1) % 3 == 0) {
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\t" << std::string(45, '-') << "\n";
}


void SudokuGame::debugBoard() {
    std::cout << "Board Debug Array\n";
    for (int y = 0; y < 9; ++y) {
        std::cout << std::format("Y {} |", y);
        for (int x = 0; x < 9; ++x) {
            std::cout << std::format("{},", board[y][x]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
