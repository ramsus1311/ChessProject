#pragma once
#include <memory>
#include "Square.h"
#include <array>

class Board {
    private:
        std::array<std::array<std::unique_ptr<Square>, 8>, 8> squares;
        void constructBoard();
    public:
        Board();
        const Square& getSquare(int row, int col) const;

        
};