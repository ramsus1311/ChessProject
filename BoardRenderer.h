#pragma once
#include "raylib.h"
#include "Board.h"

class BoardRenderer {
    private:
        const Board& board;
        int squareSize;
    public:
        BoardRenderer(const Board& board, int squareSize);
        void render(bool hasSelection, int selectedRow, int selectedCol) const;
};