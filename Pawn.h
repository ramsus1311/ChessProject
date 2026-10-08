#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    explicit Pawn(PieceColor c);

    bool isValidMove(int startCol, int startRow, int endCol, int endRow) const override;
};