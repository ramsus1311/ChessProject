#include "Pawn.h"

Pawn::Pawn(PieceColor c) : Piece(c) {}

PieceType Pawn::getType() const {
    return PieceType::Pawn;
}

bool Pawn::isValidMove(int startCol, int startRow, int endCol, int endRow) const {
    if(color == PieceColor::White) {
        if(startCol == endCol && startRow - 1 == endRow) {
            return true;
        }
        if(startCol == endCol && startRow == 6 && endRow == startRow - 2) {
            return true;
        }
    } else if(color == PieceColor::Black) {
        if(startCol == endCol && startRow + 1 == endRow) {
            return true;
        }
        if(startCol == endCol && startRow == 1 && endRow == startRow + 2) {
            return true;
        }
    }
    return false;
}