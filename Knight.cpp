#include "Knight.h"

Knight::Knight(PieceColor c) : Piece(c) {}

PieceType Knight::getType() const {
    return PieceType::Knight;
}

bool Knight::isValidMove(int startCol, int startRow, int endCol, int endRow) const {
    int colDistance = std::abs(endCol - startCol);
    int rowDistance = std::abs(endRow - startRow);

    return (colDistance == 2 && rowDistance == 1) || (colDistance == 1 && rowDistance == 2);
}