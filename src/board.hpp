#pragma once

#include "common.hpp"
#include <array>
#include <string>

// slight type abstraction
typedef unsigned char square;

enum PieceType
{
    NIL     = 0,
    PAWN    = 1,
    KNIGHT  = 2,
    BISHOP  = 3,
    ROOK    = 4,
    QUEEN   = 5,
    KING    = 6,
};

// Piece type (3 bits) and color (1 bit)
enum PieceCode
{
    EMPTY   = NIL,
    WPAWN   = PAWN,
    WKNIGHT = KNIGHT,
    WBISHOP = BISHOP,
    WROOK   = ROOK,
    WQUEEN  = QUEEN,
    WKING   = KING,

    BCODE   = 8,
    BPAWN   = BCODE + PAWN,
    BKNIGHT = BCODE + KNIGHT,
    BBISHOP = BCODE + BISHOP,
    BROOK   = BCODE + ROOK,
    BQUEEN  = BCODE + QUEEN,
    BKING   = BCODE + KING,
};

// Note empty needs to be checked separately
enum Color
{
    WHITE = 0,
    BLACK = 8,
};


// note EMPTY must be checked separately
inline int get_color(PieceCode p) {return p & 8;}


// 0x88 board size
#define BOARD_SIZE 128

// 0x88 board functions
// Coordinate transformations (all 0-indexed)
// rows 0-7 encodes ranks 1-8
// cols 0-7 encodes files a-h

inline bool is_sq(square s) {return (s & 0x88) == 0;}
inline square get_sq(int row, int col) {return (row << 4) + col;}
inline int sq_col(square s) {return s & 7;}
inline int sq_row(square s) {return s >> 4;}

// Check if string is valid algebraic coordinate
inline bool is_coord_valid(const std::string s)
{
    return (s.size() == 2 &&
            'a' <= s[0] && s[0] <= 'h' &&
            '1' <= s[1] && s[1] <= '8');
}

inline square sq_from_coord(const std::string coord)
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
class Position
{
public:
    std::array<PieceCode, BOARD_SIZE> board;
    bool black_to_move;
    uchar castle_flags;
    square ep_target; // 0xFF to store none
    int halfmove;
    int fullmove;

    // Read fen is null-terminated FEN string
    Position(const std::string& fen);
};

const square NO_EP_TARGET = -1;



const std::string START_FEN = 
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
