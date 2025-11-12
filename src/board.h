#pragma once

#include "common.h"

// slight type abstraction
typedef int piece; 
typedef unsigned char square;

enum piece_type
{
    EMPTY  = 0,
    PAWN   = 1,
    KNIGHT = 2,
    BISHOP = 3,
    ROOK   = 4,
    QUEEN  = 5,
    KING   = 6,
};
// black will be represented by negative

// 0x88 board size
#define BOARD_SIZE 128

// 0x88 board functions
// Coordinate transformations (all 0-indexed)
// rows 0-7 encodes ranks 1-8
// cols 0-7 encodes files a-h

static inline bool is_sq(square s) {return s & 0x88;}
static inline bool get_sq(int row, int col) {return (row << 4) + (col);}
static inline int sq_col(square s) {return s & 7;}
static inline int sq_row(square s) {return s >> 4;}

enum castling_flags
{
    CASTLE_WK = 1,
    CASTLE_WQ = 2,
    CASTLE_BK = 4,
    CASTLE_BQ = 8,
};

// Similar to FEN
typedef struct
{
    piece board[BOARD_SIZE];
    bool black_to_move;
    uchar castle_flags; // TODO
    square en_passant_target;
    int halfmove;
    int fullmove;
} position;

// Global position for incremental updates
// https://www.chessprogramming.org/Incremental_Updates

extern position global_pos;


// Read fen is null-terminated FEN string
void position_from_fen(const char* fen);


static const char START_FEN[] = 
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
