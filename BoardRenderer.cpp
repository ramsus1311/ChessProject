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
                const char* pieceText = "?";

                switch (piece->getType()) {
                case PieceType::Pawn:
                    pieceText = "P";
                    break;

                case PieceType::Bishop:
                    pieceText = "B";
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