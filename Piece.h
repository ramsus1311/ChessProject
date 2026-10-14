#pragma once
#include "raylib.h"
#include <memory>
#include <cmath>

enum class PieceType { Pawn, Bishop, Knight, Rook, Queen, King };

enum class PieceColor { White, Black, None };

class Piece {
public:
    PieceColor color;
    PieceType type;
    bool hasMoved;

    explicit Piece(PieceColor c) : color(c), hasMoved(false) {}

     virtual ~Piece() = default;

     void markAsMoved() {
         hasMoved = true;
     }

     virtual bool isValidMove(int startX, int startY, int endX, int endY) const = 0;

     virtual PieceType getType() const = 0;
};