#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
    explicit Rook(PieceColor c);

    PieceType getType() const override;

    bool isValidMove(int startCol, int startRow, int endCol, int endRow) const override;
};