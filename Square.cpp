#include "Square.h"
using namespace std;

Square::Square(int row, int col) : row(row), col(col), piece(nullptr) {}

int Square::getRow() const {
    return row;
}

int Square::getCol() const {
    return col;
}

bool Square::hasPiece() const {
    return piece != nullptr;
}

const Piece* Square::getPiece() const {
    return piece.get();
}

void Square::setPiece(unique_ptr<Piece> piece) {
    this->piece = move(piece);
}