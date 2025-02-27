#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H
#include <array>

class SudokuGame {

public:
    SudokuGame();
    void playGame();

private:
    std::array<std::array<char, 9>, 9> board;
    std::array<std::array<char, 9>, 9> gameBoard;
    void initBoard();
    void printBoard(const std::array<std::array<char, 9>, 9>& board);
    void debugBoard();
    void shuffleBoard();
    bool fillBoard(std::array<std::array<char, 9>, 9>& board, int row = 0, int col = 0);
    bool isValidMove(const std::array<std::array<char, 9>, 9>& board, int row, int col, char num);
    void removeCells(std::array<std::array<char, 9>, 9>& gameBoard, int maxPerBlock);
    //void removeCells(std::array<std::array<char, 9>, 9>& gameBoard, int cellsToRemove);


};

#endif
