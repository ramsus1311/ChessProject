#include "Board.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
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
    // Place white pieces
    placePiece(7, 2, make_unique<Bishop>(PieceColor::White));
    placePiece(7, 5, make_unique<Bishop>(PieceColor::White));
    placePiece(7, 1, make_unique<Knight>(PieceColor::White));
    placePiece(7, 6, make_unique<Knight>(PieceColor::White));
    placePiece(7, 0, make_unique<Rook>(PieceColor::White));
    placePiece(7, 7, make_unique<Rook>(PieceColor::White));
    placePiece(7, 3, make_unique<Queen>(PieceColor::White));
    placePiece(7, 4, make_unique<King>(PieceColor::White));

    for (int col = 0; col < 8; col++) { 
        placePiece(6, col, make_unique<Pawn>(PieceColor::White));
    }

    // Place black pieces
    placePiece(0, 2, make_unique<Bishop>(PieceColor::Black));
    placePiece(0, 5, make_unique<Bishop>(PieceColor::Black));
    placePiece(0, 1, make_unique<Knight>(PieceColor::Black));
    placePiece(0, 6, make_unique<Knight>(PieceColor::Black));
    placePiece(0, 0, make_unique<Rook>(PieceColor::Black));
    placePiece(0, 7, make_unique<Rook>(PieceColor::Black));
    placePiece(0, 3, make_unique<Queen>(PieceColor::Black));
    placePiece(0, 4, make_unique<King>(PieceColor::Black));

    for (int col = 0; col < 8; col++) {
        placePiece(1, col, make_unique<Pawn>(PieceColor::Black));
    }
}

bool Board::isPathClear(int startRow, int startCol, int endRow, int endCol) const {
    int rowStep = (endRow > startRow) - ( endRow < startRow);
    int colStep = (endCol > startCol) - ( endCol < startCol);

    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    while (currentRow != endRow || currentCol != endCol) {
        if (getSquare(currentRow, currentCol).hasPiece()) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }
    return true;
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    
    const Piece* sourcePiece = squares.at(startRow).at(startCol)->getPiece();
    const Piece* targetPiece = squares.at(endRow).at(endCol)->getPiece();

    int rookCol = -1;
    int rookDestinationCol = -1;
    
    if(sourcePiece == nullptr) {
        return false;
    }

    bool isCastlingMove = sourcePiece->getType() == PieceType::King && startCol == 4 && startRow == endRow && abs(endCol - startCol) == 2;

    if(!isCastlingMove && !sourcePiece->isValidMove(startCol, startRow, endCol, endRow)) {
        return false;
    }

    if (isCastlingMove) {
        if (endCol == 6) {
            rookCol = 7;
            rookDestinationCol = 5;
        } else if (endCol == 2) {
            rookCol = 0;
            rookDestinationCol = 3;
        } else {
            return false;
        }

        int direction = endCol > startCol ? 1 : -1;

        for(int col = startCol + direction; col != rookCol; col += direction) {
            if(squares.at(startRow).at(col)->hasPiece()) {
                return false;
            }
        }

        const Piece* rookPiece =
            squares.at(startRow).at(rookCol)->getPiece();

        if (sourcePiece->hasMoved ||
            rookPiece == nullptr ||
            rookPiece->getType() != PieceType::Rook ||
            rookPiece->color != sourcePiece->color ||
            rookPiece->hasMoved) {
            return false;
        }
    }

    if (isCastlingMove) {
        unique_ptr<Piece> movingKing =
            squares.at(startRow).at(startCol)->removePiece();

        unique_ptr<Piece> movingRook =
            squares.at(startRow).at(rookCol)->removePiece();

        movingKing->markAsMoved();
        movingRook->markAsMoved();

        squares.at(endRow).at(endCol)->setPiece(move(movingKing));
        squares.at(startRow).at(rookDestinationCol)
            ->setPiece(move(movingRook));

        return true;
    }

    if(sourcePiece->getType() == PieceType::Pawn) {
        int rowDifference = endRow - startRow;
        int colDifference = abs(endCol - startCol);

        bool isDiagonalMove = colDifference == 1;

        if(isDiagonalMove) {
            if(targetPiece == nullptr || targetPiece->color == sourcePiece->color) {
                return false;
            }
        } else {
            if(targetPiece != nullptr) {
                return false;
            }
            if(abs(rowDifference) == 2) {
                int middleRow = (startRow + endRow) / 2;
                
                if(getSquare(middleRow, startCol).hasPiece()) {
                    return false;
                }
            }
        }
    }

    if(targetPiece != nullptr && targetPiece->color == sourcePiece->color) {
        return false;
    }

    if(sourcePiece->getType() == PieceType::Bishop || sourcePiece->getType() == PieceType::Rook || sourcePiece->getType() == PieceType::Queen) {
        if(!isPathClear(startRow, startCol, endRow, endCol)) {
            return false;
        }
    }

    unique_ptr<Piece> movingPiece = squares.at(startRow).at(startCol)->removePiece();

    movingPiece->markAsMoved();
    
    squares.at(endRow).at(endCol)->setPiece(move(movingPiece));
    
    return true;
}
