#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    explicit Pawn(Color c) : Piece(c) {}

    bool isValidMove(int startX, int startY, int endX, int endY) const override {
        
        }
    };