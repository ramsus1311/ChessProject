#pragma once
#include "raylib.h"
#include <memory>
#include <cmath>

enum class PieceColor { White, Black, None };

class Piece {
public:
    PieceColor color;

    explicit Piece(PieceColor c) : color(c) {}

     virtual ~Piece() = default;

     virtual bool isValidMove(int startX, int startY, int endX, int endY) const = 0;
};