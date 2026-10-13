#include "Queen.h"

Queen::Queen(PieceColor c) : Piece(c) {}

PieceType Queen::getType() const {
    return PieceType::Queen;
}

bool Queen::isValidMove(int startCol, int startRow, int endCol, int endRow) const {
    if (startCol == endCol && startRow != endRow) {
        return true;
    } else if (startRow == endRow && startCol != endCol) {
        return true;
    } else if ( abs(endCol - startCol) == abs(endRow - startRow)) {
        return true;
    }
    return false;
}