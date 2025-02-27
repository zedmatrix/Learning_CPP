#include <iostream>
#include <string>
#include <format>
#include <algorithm>
#include <random>
#include <ctime>
#include "Sudoku.h"
#include "Input.h"

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
    int iX{0}, iY{0}, iNum{0};


    Input input;

    while (iX == 0) {
        iX = input.getXCoord();
        std::cout << std::endl;
    }
    while (iY == 0) {
        iY = input.getYCoord();
        std::cout << std::endl;
    }
    while (iNum == 0) {
        iNum = input.getNumber();
        std::cout << std::endl;
    }

    // Convert to zero based
    int zX = iX - 1;
    int zY = iY - 1;
    std::cout << std::format("X Coord:{} 0-Based:{} \tY Coord:{} 0-Based:{}\n", iX, zX, iY, zY);
    std::cout << std::format("Replacing: {} With: {}\n", gameBoard[zY][zX], iNum);
    gameBoard[zY][zX] = char(iNum + '0');
    printBoard(gameBoard);
    std::cout << std::endl;
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
