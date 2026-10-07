#include "BoardRenderer.h"
#include <string>

using namespace std;

BoardRenderer::BoardRenderer(const Board& board, int squareSize) : board(board), squareSize(squareSize) {}

void BoardRenderer::render() const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Square& square = board.getSquare(row, col);

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
        }
    }
    
}