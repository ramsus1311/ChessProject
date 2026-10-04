#pragma once
#include <memory>
#include <cmath>

enum class Color { WHITE, BLACK, NONE };

class Piece {
public:
    Color color;

    explicit Piece(Color c) : color(c) {}

     virtual ~Piece() = default;

     virtual bool isValidMove(int startX, int startY, int endX, int endY) const = 0;
};