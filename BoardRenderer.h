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
        void drawPawn(int row, int col, PieceColor color) const;
        void drawBishop(int row, int col, PieceColor color) const;
        void drawKnight(int row, int col, PieceColor color) const;
        void drawRook(int row, int col, PieceColor color) const;
        void drawQueen(int row, int col, PieceColor color) const;
        void drawKing(int row, int col, PieceColor color) const;
};