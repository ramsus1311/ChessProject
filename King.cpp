#include "King.h"

King::King(PieceColor c) : Piece(c) {}

PieceType King::getType() const {
    return PieceType::King;
}

bool King::isValidMove(int startCol, int startRow, int endCol, int endRow) const {
    int colDiff = abs(endCol - startCol);
    int rowDiff = abs(endRow - startRow);

    return (colDiff <= 1 && rowDiff <= 1) && !(colDiff == 0 && rowDiff == 0);
}