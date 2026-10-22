#include "Board.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
using namespace std;

Board::Board() : lastMoveWasPawnDoubleStep(false), lastMoveEndCol(-1), lastMoveEndRow(-1) {
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

bool Board::isSquareUnderAttack(int row, int col, PieceColor byColor) const{
    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 8; c++) {
            const Piece* piece = squares.at(r).at(c)->getPiece();
            if(piece != nullptr && piece->color == byColor) {
                if(piece->getType() == PieceType::Pawn) {
                    int direction = piece->color == PieceColor::White ? -1 : 1;
                    if(row == r + direction && abs(col - c) == 1) {
                        return true;
                    }
                    continue;
                }
                if(piece->getType() == PieceType::Bishop ||
                   piece->getType() == PieceType::Rook ||
                   piece->getType() == PieceType::Queen) {
                    if(piece->isValidMove(c, r, col, row) && isPathClear(r, c, row, col)) {
                        return true;
                    }
                    continue;
                }
                if(piece->isValidMove(c, r, col, row)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::findKing(PieceColor color, int& kingRow, int& kingCol) const {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            const Piece* piece = squares.at(row).at(col)->getPiece();
            if(piece != nullptr && piece->getType() == PieceType::King && piece->color == color) {
                kingRow = row;
                kingCol = col;
                return true;
            }
        }
    }
    return false;
}

bool Board::isInCheck(PieceColor color) const {
    int kingRow = -1;
    int kingCol = -1;

    if(!findKing(color, kingRow, kingCol)) {
        return false;
    }

    PieceColor opponentColor = (color == PieceColor::White) ? PieceColor::Black : PieceColor::White;

    return isSquareUnderAttack(kingRow, kingCol, opponentColor);
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    
    const Piece* sourcePiece = squares.at(startRow).at(startCol)->getPiece();
    const Piece* targetPiece = squares.at(endRow).at(endCol)->getPiece();
    
    bool isEnPassant = false; 
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

        PieceColor opponentColor =
            sourcePiece->color == PieceColor::White
                ? PieceColor::Black
                : PieceColor::White;

        for (int col = startCol;
            col != endCol + direction;
            col += direction) {
            if (isSquareUnderAttack(startRow, col, opponentColor)) {
                return false;
            }
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
        
        lastMoveWasPawnDoubleStep = false;
        lastMoveEndRow = -1;
        lastMoveEndCol = -1;

        return true;
    }

    if(sourcePiece->getType() == PieceType::Pawn) {
        int rowDifference = endRow - startRow;
        int colDifference = abs(endCol - startCol);

        bool isDiagonalMove = colDifference == 1;

        if(isDiagonalMove) {
            if(targetPiece == nullptr) {
                const Piece* adjacentPiece =
                    squares.at(startRow).at(endCol)->getPiece();

                if(lastMoveWasPawnDoubleStep &&
                    lastMoveEndRow == startRow &&
                    lastMoveEndCol == endCol &&
                    adjacentPiece != nullptr &&
                    adjacentPiece->getType() == PieceType::Pawn &&
                    adjacentPiece->color != sourcePiece->color) {
                    isEnPassant = true;
                } else {
                    return false;
                }
            } else if(targetPiece->color == sourcePiece->color) {
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

    PieceColor movingColor = sourcePiece->color;
    bool previousHasMoved = sourcePiece->hasMoved;

    bool previousLastMoveWasPawnDoubleStep =
        lastMoveWasPawnDoubleStep;
    int previousLastMoveEndRow = lastMoveEndRow;
    int previousLastMoveEndCol = lastMoveEndCol;

    unique_ptr<Piece> capturedPiece =
        squares.at(endRow).at(endCol)->removePiece();

    unique_ptr<Piece> enPassantCapturedPiece = nullptr;

    if (isEnPassant) {
        enPassantCapturedPiece =
            squares.at(startRow).at(endCol)->removePiece();
    }

    bool currentMoveWasPawnDoubleStep =
        sourcePiece->getType() == PieceType::Pawn &&
        abs(endRow - startRow) == 2;

    unique_ptr<Piece> movingPiece =
        squares.at(startRow).at(startCol)->removePiece();

    movingPiece->markAsMoved();

    squares.at(endRow).at(endCol)
        ->setPiece(move(movingPiece));

    lastMoveWasPawnDoubleStep =
        currentMoveWasPawnDoubleStep;

    if (lastMoveWasPawnDoubleStep) {
        lastMoveEndRow = endRow;
        lastMoveEndCol = endCol;
    } else {
        lastMoveEndRow = -1;
        lastMoveEndCol = -1;
    }

    if (isInCheck(movingColor)) {
        unique_ptr<Piece> movedPiece =
            squares.at(endRow).at(endCol)->removePiece();

        movedPiece->hasMoved = previousHasMoved;

        squares.at(startRow).at(startCol)
            ->setPiece(move(movedPiece));

        if (capturedPiece != nullptr) {
            squares.at(endRow).at(endCol)
                ->setPiece(move(capturedPiece));
        }

        if (enPassantCapturedPiece != nullptr) {
            squares.at(startRow).at(endCol)
                ->setPiece(move(enPassantCapturedPiece));
        }

        lastMoveWasPawnDoubleStep =
            previousLastMoveWasPawnDoubleStep;
        lastMoveEndRow = previousLastMoveEndRow;
        lastMoveEndCol = previousLastMoveEndCol;

        return false;
    }

    return true;
}
