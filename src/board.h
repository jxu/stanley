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

static inline bool is_black(piece s) {return s < 0;}

static inline bool is_sq(square s) {return (s & 0x88) == 0;}
static inline square get_sq(int row, int col) {return (row << 4) + (col);}
static inline int sq_col(square s) {return s & 7;}
static inline int sq_row(square s) {return s >> 4;}

// Check if string is valid algebraic coordinate
static inline bool is_coord_valid(const char* s)
{
    assert(s != NULL);
    return (strlen(s) == 2 && 
            'a' <= s[0] && s[0] <= 'h' &&
            '1' <= s[1] && s[1] <= '8');
}

static inline int sq_from_coord(const char* coord)
{
    assert(is_coord_valid(coord));
    int row = coord[1] - '1';
    int col = coord[0] - 'a';
    return get_sq(row, col);
}

// used to index into a castling nibble
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
