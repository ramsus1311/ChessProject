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
                } else {
                    const char* pieceText = "?";

                    switch (piece->getType()) {
                    case PieceType::Bishop:
                        pieceText = "B";
                        break;
                    
                    case PieceType::Knight:
                        pieceText = "N";
                        break;

                    case PieceType::Rook:
                        pieceText = "R";
                        break;
                    
                        case PieceType::Queen:
                        pieceText = "Q";
                        break;
                        
                    case PieceType::King:
                        pieceText = "K";
                        break;

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
    const int centerY = squareY + squareSize / 2 + 8;
    
    DrawCircle(centerX, centerY - 28, 14, outlineColor);
    DrawCircle(centerX, centerY - 28, 11, pawnColor);

    DrawRectangle(centerX - 6, centerY - 18, 12, 10, outlineColor);
    DrawRectangle(centerX - 4, centerY - 18, 8, 10, pawnColor);

    DrawTriangle(
        {static_cast<float>(centerX - 21), static_cast<float>(centerY + 18)},
        {static_cast<float>(centerX + 21), static_cast<float>(centerY + 18)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 10)},
        outlineColor
    );

    DrawTriangle(
        {static_cast<float>(centerX - 17), static_cast<float>(centerY + 15)},
        {static_cast<float>(centerX + 17), static_cast<float>(centerY + 15)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 7)},
        pawnColor
    );

    DrawRectangle(centerX - 25, centerY + 16, 50, 9, outlineColor);
    DrawRectangle(centerX - 21, centerY + 16, 42, 5, pawnColor);
}

void BoardRenderer::drawBishop(int row, int col, PieceColor color) const {
    Color bishopColor =
        color == PieceColor::White ? RAYWHITE : BLACK;
    Color outlineColor =
        color == PieceColor::White ? DARKGRAY : RAYWHITE;

    const int squareX = col * squareSize;
    const int squareY = row * squareSize;
    const int centerX = squareX + squareSize / 2;
    const int centerY = squareY + squareSize / 2 + 8;

    // Base
    DrawRectangle(centerX - 24, centerY + 16, 48, 9, outlineColor);
    DrawRectangle(centerX - 20, centerY + 16, 40, 5, bishopColor);

    // Body
    DrawTriangle(
        {static_cast<float>(centerX - 19), static_cast<float>(centerY + 16)},
        {static_cast<float>(centerX + 19), static_cast<float>(centerY + 16)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 20)},
        outlineColor
    );
    DrawTriangle(
        {static_cast<float>(centerX - 15), static_cast<float>(centerY + 13)},
        {static_cast<float>(centerX + 15), static_cast<float>(centerY + 13)},
        {static_cast<float>(centerX), static_cast<float>(centerY - 15)},
        bishopColor
    );

    // Mitre
    DrawCircle(centerX, centerY - 25, 11, outlineColor);
    DrawCircle(centerX, centerY - 25, 8, bishopColor);

    // Bishop's diagonal slit
    DrawLine(
        centerX - 5,
        centerY - 30,
        centerX + 5,
        centerY - 20,
        outlineColor
    );
}