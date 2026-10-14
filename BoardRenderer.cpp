#include "BoardRenderer.h"
#include "Bishop.h"
#include "Pawn.h"
#include <string>

using namespace std;

BoardRenderer::BoardRenderer(const Board& board, int squareSize) : board(board), squareSize(squareSize) {}

void BoardRenderer::render(bool hasSelection, int selectedRow, int selectedCol) const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Square& square = board.getSquare(row, col);

            const Piece* piece = square.getPiece();

            bool isLightSquare = (row + col) % 2 == 0;
            Color squareColor = isLightSquare ? RAYWHITE : DARKGRAY;
            DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, squareColor);

            if (col == 7) {
                    int rank = 8 - row ;
                    string text = to_string(rank);

                    int x = col * squareSize + 80;
                    int y = row * squareSize + 10;

                    DrawText(text.c_str(), x, y, 20, BLACK);
            }

            if (row == 7) {
                char file = 'a' + col;
                string text(1, file);

                int x = col * squareSize + 10;
                int y = row * squareSize + squareSize - 30;

                DrawText(text.c_str(), x, y, 20, BLACK);
            }

            if (hasSelection && row == selectedRow && col == selectedCol) {
                DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, YELLOW);
            }

            if (piece != nullptr) {
                if(piece->getType() == PieceType::Pawn) {
                    drawPawn(row, col, piece->color);
                } else if (piece->getType() == PieceType::Bishop) {
                    drawBishop(row, col, piece->color);
                } else if (piece->getType() == PieceType::Knight) {
                    drawKnight(row, col, piece->color);
                } else if (piece->getType() == PieceType::Rook) {
                    drawRook(row, col, piece->color);
                } else if (piece->getType() == PieceType::Queen) {
                    drawQueen(row, col, piece->color);
                } else if (piece->getType() == PieceType::King) {
                    drawKing(row, col, piece->color);
                } else {
                    const char* pieceText = "?";

                    switch (piece->getType()) {
                    default:
                        break;
                    }

                    int textX = col * squareSize + squareSize / 2 - 10;
                    int textY = row * squareSize + squareSize / 2 - 20;

                    DrawText(pieceText, textX, textY, 40, BLACK);
                }
            }
        }
    }
}

void BoardRenderer::drawPawn(int row, int col, PieceColor color) const {
    Color pawnColor =
        color == PieceColor::White ? RAYWHITE : BLACK;
    Color outlineColor =
        color == PieceColor::White ? DARKGRAY : RAYWHITE;

    const int squareX = col * squareSize;
    const int squareY = row * squareSize;
    const int centerX = squareX + squareSize / 2;
    const int centerY = squareY + squareSize / 2 + 10;

    DrawRectangle(centerX - 20, centerY + 18, 40, 9, outlineColor);
    DrawRectangle(centerX - 16, centerY + 18, 32, 5, pawnColor);
    DrawTriangle(
        {static_cast<float>(centerX - 12), static_cast<float>(centerY + 17)},
        {static_cast<float>(centerX + 12), static_cast<float>(centerY + 17)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 5)},
        outlineColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 8), static_cast<float>(centerY + 14)},
        {static_cast<float>(centerX + 8), static_cast<float>(centerY + 14)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 3)},
        pawnColor
    );
    DrawCircle(centerX, centerY - 12, 11, outlineColor);
    DrawCircle(centerX, centerY - 12, 8, pawnColor);
}

void BoardRenderer::drawBishop(int row, int col, PieceColor color) const {
    Color bishopColor =
        color == PieceColor::White ? RAYWHITE : BLACK;
    Color outlineColor =
        color == PieceColor::White ? DARKGRAY : RAYWHITE;

    const int squareX = col * squareSize;
    const int squareY = row * squareSize;
    const int centerX = squareX + squareSize / 2;
    const int centerY = squareY + squareSize / 2 + 10;

    DrawRectangle(centerX - 23, centerY + 19, 46, 9, outlineColor);
    DrawRectangle(centerX - 19, centerY + 19, 38, 5, bishopColor);
    DrawTriangle(
        {static_cast<float>(centerX - 17), static_cast<float>(centerY + 17)},
        {static_cast<float>(centerX + 17), static_cast<float>(centerY + 17)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 30)},
        outlineColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 12), static_cast<float>(centerY + 13)},
        {static_cast<float>(centerX + 12), static_cast<float>(centerY + 13)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 27)},
        bishopColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 11), static_cast<float>(centerY - 25)},
        {static_cast<float>(centerX + 11), static_cast<float>(centerY - 25)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 46)},
        outlineColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 7), static_cast<float>(centerY - 26)},
        {static_cast<float>(centerX + 7), static_cast<float>(centerY - 26)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 42)},
        bishopColor
    );
    DrawLine(centerX - 4, centerY - 39, centerX + 5, centerY - 28, outlineColor);
}

void BoardRenderer::drawKnight(int row, int col, PieceColor color) const {
    Color knightColor =
        color == PieceColor::White ? RAYWHITE : BLACK;
    Color outlineColor =
        color == PieceColor::White ? DARKGRAY : RAYWHITE;

    const int squareX = col * squareSize;
    const int squareY = row * squareSize;
    const int centerX = squareX + squareSize / 2;
    const int centerY = squareY + squareSize / 2 + 10;

    DrawRectangle(centerX - 23, centerY + 19, 46, 9, outlineColor);
    DrawRectangle(centerX - 19, centerY + 19, 38, 5, knightColor);
    // Solid outline: a straight chest and a rounded horse head.
    DrawRectangle(centerX - 19, centerY - 35, 24, 54, outlineColor);
    DrawTriangle(
        {static_cast<float>(centerX - 19), static_cast<float>(centerY - 35)},
        {static_cast<float>(centerX + 5), static_cast<float>(centerY - 35)},
        {static_cast<float>(centerX + 26), static_cast<float>(centerY - 15)},
        outlineColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 19), static_cast<float>(centerY + 18)},
        {static_cast<float>(centerX + 26), static_cast<float>(centerY - 15)},
        {static_cast<float>(centerX + 26), static_cast<float>(centerY + 9)},
        outlineColor
    );
    DrawCircle(centerX + 7, centerY - 30, 19, outlineColor);

    // Inner shape leaves a bold outline while keeping the silhouette simple.
    DrawRectangle(centerX - 15, centerY - 31, 16, 46, knightColor);
    DrawTriangle(
        {static_cast<float>(centerX - 15), static_cast<float>(centerY - 31)},
        {static_cast<float>(centerX + 1), static_cast<float>(centerY - 31)},
        {static_cast<float>(centerX + 21), static_cast<float>(centerY - 13)},
        knightColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 15), static_cast<float>(centerY + 14)},
        {static_cast<float>(centerX + 21), static_cast<float>(centerY - 13)},
        {static_cast<float>(centerX + 21), static_cast<float>(centerY + 5)},
        knightColor
    );
    DrawCircle(centerX + 7, centerY - 30, 15, knightColor);

    // Diagonal cut, ear, and eye make the horse profile recognizable.
    DrawTriangle(
        {static_cast<float>(centerX - 10), static_cast<float>(centerY + 14)},
        {static_cast<float>(centerX + 11), static_cast<float>(centerY - 22)},
        {static_cast<float>(centerX + 20), static_cast<float>(centerY - 22)},
        outlineColor
    );
    DrawTriangle(
        {static_cast<float>(centerX + 1), static_cast<float>(centerY - 38)},
        {static_cast<float>(centerX + 7), static_cast<float>(centerY - 51)},
        {static_cast<float>(centerX + 12), static_cast<float>(centerY - 35)},
        outlineColor
    );
    DrawCircle(centerX + 4, centerY - 31, 3, outlineColor);
    DrawCircle(centerX + 4, centerY - 31, 1, knightColor);
}

void BoardRenderer::drawRook(int row, int col, PieceColor color) const {
    Color rookColor =
        color == PieceColor::White ? RAYWHITE : BLACK;
    Color outlineColor =
        color == PieceColor::White ? DARKGRAY : RAYWHITE;

    const int squareX = col * squareSize;
    const int squareY = row * squareSize;
    const int centerX = squareX + squareSize / 2;
    const int centerY = squareY + squareSize / 2 + 10;

    DrawRectangle(centerX - 23, centerY + 19, 46, 9, outlineColor);
    DrawRectangle(centerX - 19, centerY + 19, 38, 5, rookColor);
    DrawRectangle(centerX - 16, centerY - 28, 32, 48, outlineColor);
    DrawRectangle(centerX - 12, centerY - 24, 24, 44, rookColor);
    DrawRectangle(centerX - 21, centerY - 34, 42, 11, outlineColor);
    DrawRectangle(centerX - 17, centerY - 31, 8, 6, rookColor);
    DrawRectangle(centerX - 4, centerY - 31, 8, 6, rookColor);
    DrawRectangle(centerX + 9, centerY - 31, 8, 6, rookColor);
}

void BoardRenderer::drawQueen(int row, int col, PieceColor color) const {
    Color queenColor =
        color == PieceColor::White ? RAYWHITE : BLACK;
    Color outlineColor =
        color == PieceColor::White ? DARKGRAY : RAYWHITE;

    const int squareX = col * squareSize;
    const int squareY = row * squareSize;
    const int centerX = squareX + squareSize / 2;
    const int centerY = squareY + squareSize / 2 + 10;

    DrawRectangle(centerX - 25, centerY + 19, 50, 9, outlineColor);
    DrawRectangle(centerX - 21, centerY + 19, 42, 5, queenColor);
    DrawTriangle(
        {static_cast<float>(centerX - 18), static_cast<float>(centerY + 16)},
        {static_cast<float>(centerX + 18), static_cast<float>(centerY + 16)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 22)},
        outlineColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 13), static_cast<float>(centerY + 13)},
        {static_cast<float>(centerX + 13), static_cast<float>(centerY + 13)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 18)},
        queenColor
    );
    DrawCircle(centerX - 17, centerY - 20, 6, outlineColor);
    DrawCircle(centerX, centerY - 43, 6, outlineColor);
    DrawCircle(centerX + 17, centerY - 20, 6, outlineColor);
    DrawCircle(centerX - 17, centerY - 20, 3, queenColor);
    DrawCircle(centerX, centerY - 43, 3, queenColor);
    DrawCircle(centerX + 17, centerY - 20, 3, queenColor);
}

void BoardRenderer::drawKing(int row, int col, PieceColor color) const {
    Color kingColor =
        color == PieceColor::White ? RAYWHITE : BLACK;
    Color outlineColor =
        color == PieceColor::White ? DARKGRAY : RAYWHITE;

    const int squareX = col * squareSize;
    const int squareY = row * squareSize;
    const int centerX = squareX + squareSize / 2;
    const int centerY = squareY + squareSize / 2 + 10;

    DrawRectangle(centerX - 25, centerY + 19, 50, 9, outlineColor);
    DrawRectangle(centerX - 21, centerY + 19, 42, 5, kingColor);
    DrawTriangle(
        {static_cast<float>(centerX - 19), static_cast<float>(centerY + 16)},
        {static_cast<float>(centerX + 19), static_cast<float>(centerY + 16)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 28)},
        outlineColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 14), static_cast<float>(centerY + 13)},
        {static_cast<float>(centerX + 14), static_cast<float>(centerY + 13)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 24)},
        kingColor
    );
    DrawRectangle(centerX - 6, centerY - 53, 12, 27, outlineColor);
    DrawRectangle(centerX - 14, centerY - 46, 28, 11, outlineColor);
    DrawRectangle(centerX - 3, centerY - 51, 6, 23, kingColor);
    DrawRectangle(centerX - 10, centerY - 43, 20, 5, kingColor);
}