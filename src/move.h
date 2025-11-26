#pragma once
#include "board.h"

// Move encoding naively for now

typedef struct
{
    square from;
    square to;
    PieceType  promotion;
} Move;

// Init with struct initializers list

// Write 2 chars of square coord and returns new pointer
static inline char* write_coord(char* buf, square sq)
{
    assert(is_sq(sq));
    buf[0] = sq_col(sq) + 'a';
    buf[1] = sq_row(sq) + '1';
    return buf + 2;
}

// Writes move in UCI algebraic notation to buffer
// Returns pointer to new end (no space)
static inline char* write_move(char* buf, Move move)
{
    buf = write_coord(buf, move.from); 
    buf = write_coord(buf, move.to);

    switch (move.promotion)
    {
        case KNIGHT: *buf++ = 'n'; break;
        case BISHOP: *buf++ = 'b'; break;
        case ROOK:   *buf++ = 'r'; break;
        case QUEEN:  *buf++ = 'q'; break;
        default: ;
    }
   
    return buf;
}
