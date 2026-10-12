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

    explicit Piece(PieceColor c) : color(c) {}

     virtual ~Piece() = default;

     virtual bool isValidMove(int startX, int startY, int endX, int endY) const = 0;

     virtual PieceType getType() const = 0;
};