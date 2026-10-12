#include "Board.h"
#include "Bishop.h"
#include "Pawn.h"
using namespace std;

Board::Board() {
    constructBoard();
    setupInitialPieces();
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

void Board::setupInitialPieces() {
    // Place white bishops
    placePiece(7, 2, make_unique<Bishop>(PieceColor::White));
    placePiece(7, 5, make_unique<Bishop>(PieceColor::White));

    // Place white pawns
    for (int col = 0; col < 8; col++) {
        placePiece(6, col, make_unique<Pawn>(PieceColor::White));
    }

    // Place black bishops
    placePiece(0, 2, make_unique<Bishop>(PieceColor::Black));
    placePiece(0, 5, make_unique<Bishop>(PieceColor::Black));

    // Place black pawns
    for (int col = 0; col < 8; col++) {
        placePiece(1, col, make_unique<Pawn>(PieceColor::Black));
    }
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    const Piece* piece = squares.at(startRow).at(startCol)->getPiece();
    if(piece == nullptr) {
        return false;
    }

    if(!piece->isValidMove(startCol, startRow, endCol, endRow)) {
        return false;
    }

    unique_ptr<Piece> movingPiece = squares.at(startRow).at(startCol)->removePiece();
    squares.at(endRow).at(endCol)->setPiece(move(movingPiece));
    return true;
}
