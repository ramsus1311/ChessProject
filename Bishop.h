#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
    explicit Bishop(PieceColor c);

    PieceType getType() const override;

    bool isValidMove(int startCol, int startRow, int endCol, int endRow) const override;
};