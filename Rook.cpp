#include "Rook.h"

Rook::Rook(PieceColor c) : Piece(c) {}

PieceType Rook::getType() const {
    return PieceType::Rook;
}

bool Rook::isValidMove(int startCol, int startRow, int endCol, int endRow) const {
    if (startCol == endCol && startRow != endRow) {
        return true;
    } else if (startRow == endRow && startCol != endCol) {
        return true;
    }
}