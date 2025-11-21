#include "move.hpp"

Move init_move(square from, square to, bool capture, PieceType promotion)
{
    Move move =
    {
        .from = from,
        .to = to,
        .capture = capture,
        .promotion = promotion
    };
    return move;
}
