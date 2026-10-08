#pragma once
#include <memory>
#include "Square.h"
#include <array>

class Board {
    private:
        std::array<std::array<std::unique_ptr<Square>, 8>, 8> squares;
        void constructBoard();
        void setupInitialPieces();
    public:
        Board();
        const Square& getSquare(int row, int col) const;
        void placePiece(int row, int col, std::unique_ptr<Piece> piece);
        void movePiece(int startRow, int startCol, int endRow, int endCol);
};