#pragma once
#include "raylib.h"
#include "Board.h"

class Game {
private:
    bool hasSelection;
    int startRow;
    int startCol;
    Board& board;
    int squareSize;
    PieceColor currentTurn;
    void switchTurn();
public:
    Game(Board& board, int squareSize);
    void handleInput();
    bool isSelected() const;
    int getSelectedRow() const;
    int getSelectedCol() const;
};