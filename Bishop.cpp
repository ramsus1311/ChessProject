#include "Bishop.h"

Bishop::Bishop(PieceColor c) : Piece(c) {}

PieceType Bishop::getType() const {
    return PieceType::Bishop;
}

bool Bishop::isValidMove(int startCol, int startRow, int endCol, int endRow) const {
    int colDistance = abs(endCol - startCol);
    int rowDistance = abs(endRow - startRow);
    
    return colDistance != 0 && colDistance == rowDistance;
}