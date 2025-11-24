#include "board.hpp"

// Move encoding naively for now
// https://www.chessprogramming.org/Encoding_Moves

class Move
{
public:
    square from;
    square to;
    bool   capture;
    PieceType  promotion;

    Move(square from, square to, bool capture=false, PieceType promotion=NIL) :
    from(from),
    to(to),
    capture(capture),
    promotion(promotion)
    {}

    std::string to_string(void);
};


