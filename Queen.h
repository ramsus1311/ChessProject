#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
    explicit Queen(PieceColor c);

    PieceType getType() const override;

    bool isValidMove(int startCol, int startRow, int endCol, int endRow) const override;
};