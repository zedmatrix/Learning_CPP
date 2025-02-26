#include "TicTacToeGame.h"
#include <format>
#include <iostream>

TicTacToeGame::TicTacToeGame() {
}

//Public function
void TicTacToeGame::playGame() {
    clearBoard();
    char player1 = 'X';
    char player2 = 'O';

    char currentPlayer = player1;

    bool isDone = false;
    int x, y;
    int turn = 0;

    while (isDone == false) {
        printBoard();
        std::cout << std::format("\tPlayer {} Turn {}\n", currentPlayer, turn);
        x = getXCoord();
        y = getYCoord();

        if (placeMarker(x, y, currentPlayer) == false) {
            std::cout << "Invalid Spot!\n";
        } else {
            turn++;
            if (checkForVictory(currentPlayer) == true) {
                std::cout << std::format("\t\n The Game is Over! The Winner is {}\n ", currentPlayer);
                isDone = true;
                printBoard();
            } else if (turn == 9) {
                std::cout << "\t\nNo More Moves! Tie Game!\n";
                isDone = true;
                printBoard();
            }
            if (currentPlayer == player1) {
                currentPlayer = player2;
            } else {
                currentPlayer = player1;
            }
        }
    }
}

//Private functions
bool TicTacToeGame::checkForVictory(char currentPlayer) {

    // Check Rows
    for (int y = 0; y < 3; y ++) {
        if ((board[y][0] == currentPlayer) && (board[y][0] == board[y][1]) && (board[y][1] == board[y][2])) {
            return true;
        }
    }
    // Check Columns
    for (int x = 0; x < 3; x ++) {
        if ((board[0][x] == currentPlayer) && (board[0][x] == board[1][x]) && (board[1][x] == board[2][x])) {
            return true;
        }
    }
    // Check Top Right Diagonal
    if ((board[0][0] == currentPlayer) && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) {
            return true;
    }
    // Check Bottom Right Diagonal
    if ((board[2][2] == currentPlayer) && (board[2][2] == board[1][1]) && (board[1][1] == board[0][0])) {
            return true;
    }
    return false;
}

bool TicTacToeGame::placeMarker(int x, int y, char currentPlayer) {
    if (board[y][x] != ' ') {
        return false;
    }
    board[y][x] = currentPlayer;
    return true;

}

int TicTacToeGame::getXCoord() {
    int x;
    bool isInputBad = true;
    while (isInputBad == true) {
        std::cout << "Enter the X Coordinate: ";
        std::cin >> x;
        if (x < 1 || x > 3) {
            std::cout << " Invalid Coordinate!\n";
        } else {
            isInputBad = false;
        }
    }
    return x - 1;
}

int TicTacToeGame::getYCoord() {
    int y;
    bool isInputBad = true;
    while (isInputBad == true) {
        std::cout << "Enter the Y Coordinate: ";
        std::cin >> y;
        if (y < 1 || y > 3) {
            std::cout << " Invalid Coordinate!\n";
        } else {
            isInputBad = false;
        }
    }
    return y - 1;
}

void TicTacToeGame::clearBoard() {
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            board[y][x] = ' ';
        }
    }
}

void TicTacToeGame::printBoard() {
    std::cout << "\n\t X | 1 | 2 | 3 |\n";
    for (int y = 0; y < 3; ++y) {
        std::cout << std::format("\t----------------\n");
        std::cout << std::format("\tY{} | {} | {} | {} |\n",y + 1 , board[y][0], board[y][1], board[y][2]);
    }
    std::cout << std::format("\t----------------\n\n");
}
