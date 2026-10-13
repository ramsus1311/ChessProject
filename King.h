#pragma once
#include "Piece.h"

class King : public Piece {
public:
    explicit King(PieceColor c);

    PieceType getType() const override;

    bool isValidMove(int startCol, int startRow, int endCol, int endRow) const override;
};