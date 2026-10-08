#pragma once
#include "Piece.h"
#include <memory>

class Square {
    private:
        int row;
        int col;
        std::unique_ptr<Piece> piece;
    public:
        Square(int row, int col);

        int getRow() const;
        int getCol() const;

        bool hasPiece() const;
        const Piece* getPiece() const;

        void setPiece(std::unique_ptr<Piece> piece);
};