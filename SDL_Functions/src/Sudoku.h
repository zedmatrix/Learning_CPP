#ifndef SUDOKU_H
#define SUDOKU_H
#include <bits/stdc++.h>
#include <vector>

class Sudoku {

public:
    Sudoku();
    ~Sudoku();

    std::vector<std::vector<int>> sudokuGenerator();
    void removeKDigits(std::vector<std::vector<int>> &grid, int k);

private:

    bool unUsedInBox(std::vector<std::vector<int>> &grid, int rowStart, int colStart, int num);
    void fillBox(std::vector<std::vector<int>> &grid, int row, int col);
    bool unUsedInRow(std::vector<std::vector<int>> &grid, int i, int num);
    bool unUsedInCol(std::vector<std::vector<int>> &grid, int j, int num);
    bool checkIfSafe(std::vector<std::vector<int>> &grid, int i, int j, int num);
    void fillDiagonal(std::vector<std::vector<int>> &grid);
    bool fillRemaining(std::vector<std::vector<int>> &grid, int i, int j);

};

#endif //SUDOKU_H
