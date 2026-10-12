#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    explicit Knight(PieceColor c);

    PieceType getType() const override;

    bool isValidMove(int startCol, int startRow, int endCol, int endRow) const override;
};