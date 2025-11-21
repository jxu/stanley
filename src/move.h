#include "common.h"
#include "board.h"

// Move encoding naively for now


typedef struct
{
    square from;
    square to;
    bool   capture;
    PieceType  promotion;
} Move;

// Returns Move as value
Move init_move(square from, square to, bool capture, PieceType promotion);

static inline void write_square(char* buf, square sq)
{
    buf[0] = sq_col(sq) - 'a';
    buf[1] = sq_row(sq) - '1';

}

// Writes move in UCI algebraic notation to buffer
// Returns # chars written
int write_move(char* buf, Move move);
