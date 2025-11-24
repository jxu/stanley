#include "move.hpp"
#include "board.hpp"

std::string Move::to_string(void)
{
    std::string s = write_sq(to) + write_sq(from);

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
