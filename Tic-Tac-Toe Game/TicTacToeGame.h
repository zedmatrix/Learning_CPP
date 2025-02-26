#ifndef TICTACTOEGAME
#define TICTACTOEGAME
#include <array>

class TicTacToeGame {

public:
    TicTacToeGame();
    void playGame();

private:
    std::array<std::array<char, 3>, 3> board;
    void clearBoard();
    void printBoard();
    bool checkForVictory(char currentPlayer);
    bool placeMarker(int x, int y, char currentPlayer);
    int getXCoord();
    int getYCoord();
};

#endif  //TICTACTOEGAME
