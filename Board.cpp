#include "Board.h"
using namespace std;

Board::Board() {
    constructBoard();
}

void Board::constructBoard() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            squares[row][col] = make_unique<Square>(row, col);
        }
    }
}

const Square& Board::getSquare(int row, int col) const {
    return *squares.at(row).at(col);
}

void Board::placePiece(int row, int col, unique_ptr<Piece> piece) {
    squares.at(row).at(col)->setPiece(move(piece));
}

void Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    unique_ptr<Piece> piece = squares.at(startRow).at(startCol)->removePiece();

    if(piece == nullptr) {
        return;
    }

    squares.at(endRow).at(endCol)->setPiece(move(piece));
}
