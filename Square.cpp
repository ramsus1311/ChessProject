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