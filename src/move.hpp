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

    Move(square from, square to) :
    from(from),
    to(to),
    capture(false),
    promotion(NIL)
    {}

    // Write in UCI long algebraic notation
    std::string to_string(void)
    {
        std::string s = write_sq(from) + write_sq(to);

        switch (promotion)
        {
            case KNIGHT: s += 'n'; break;
            case BISHOP: s += 'b'; break;
            case ROOK:   s += 'r'; break;
            case QUEEN:  s += 'q'; break;
            default: break;
        }

        return s;
    }
};


