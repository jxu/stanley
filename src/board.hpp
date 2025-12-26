/* Piece and board definitions.

    0x88 board
    https://www.chessprogramming.org/0x88

    128-byte array stores the board. Half of the board are normal squares.
    the other half of the board is garbage, for boundary checking
    the (0-indexed) row and col are indexed in binary as 0rrr0fff
    Note that square a1 is 0x00

      a  b  c  d  e  f  g  h < file
    8 70 71 72 73 74 75 76 77|78 79 7A 7B 7C 7D 7E 7F
    7 60 61 62 63 64 65 66 67|68 69 6A 6B 6C 6D 6E 6F
    6 50 51 52 53 54 55 56 57|58 59 5A 5B 5C 5D 5E 5F
    5 40 41 42 43 44 45 46 47|48 49 4A 4B 4C 4D 4E 4F
    4 30 31 32 33 34 35 36 37|38 39 3A 3B 3C 3D 3E 3F
    3 20 21 22 23 24 25 26 27|28 29 2A 2B 2C 2D 2E 2F
    2 10 11 12 13 14 15 16 17|18 19 1A 1B 1C 1D 1E 1F
    1 00 01 02 03 04 05 06 07|08 09 0A 0B 0C 0D 0E 0F
    ^ rank

    A square is represented by an index into a 128 entry 0x88 board
    Uses an int instead of object for efficiency

    Square Coordinates are file-rank combo like h8

*/

#pragma once

#include <cassert>
#include <string>
#include <cstdint>

// slight type abstraction for 0x88 index
typedef int8_t square;

// Chess piece, independent of color
enum PieceType : int8_t
{
    NIL     = 0,
    PAWN    = 1,
    KNIGHT  = 2,
    BISHOP  = 3,
    ROOK    = 4,
    QUEEN   = 5,
    KING    = 6,
};

// Piece with color encoded as sign. 0 means "empty" piece
enum PieceCode : int8_t
{
    EMPTY   = NIL,
    WPAWN   = PAWN,
    WKNIGHT = KNIGHT,
    WBISHOP = BISHOP,
    WROOK   = ROOK,
    WQUEEN  = QUEEN,
    WKING   = KING,

    BPAWN   = -PAWN,
    BKNIGHT = -KNIGHT,
    BBISHOP = -BISHOP,
    BROOK   = -ROOK,
    BQUEEN  = -QUEEN,
    BKING   = -KING,
};

enum Color : int
{
    WHITE = 1,
    BLACK = -1,
    NEUTRAL = 0,
};

// considers EMPTY to be NEUTRAL
inline Color get_color(PieceCode p)
{
    if (p > 0) return WHITE;
    if (p < 0) return BLACK;
    return NEUTRAL;
}

inline Color invert_color(Color c)
{
    assert(c != NEUTRAL);
    return Color(-c);
}

inline PieceCode invert_piece(PieceCode p)
{
    assert(p != EMPTY);
    return PieceCode(-p);
}

inline PieceType get_type(PieceCode p)
{
    return PieceType(std::abs(p));
}

// 0x88 board size
constexpr size_t BOARD_SIZE = 128;

enum SquareConst : int8_t
{
    // enum will increment each unspecified value
    A1 = 0x00, B1, C1, D1, E1, F1, G1, H1,
    A2 = 0x10, B2, C2, D2, E2, F2, G2, H2,
    A3 = 0x20, B3, C3, D3, E3, F3, G3, H3,
    A4 = 0x30, B4, C4, D4, E4, F4, G4, H4,
    A5 = 0x40, B5, C5, D5, E5, F5, G5, H5,
    A6 = 0x50, B6, C6, D6, E6, F6, G6, H6,
    A7 = 0x60, B7, C7, D7, E7, F7, G7, H7,
    A8 = 0x70, B8, C8, D8, E8, F8, G8, H8,
};

// 0x88 board functions
// Coordinate transformations (all 0-indexed)

// rows 0-7 encodes ranks 1-8
// cols 0-7 encodes files a-h

// is value a valid 0x88 board square
inline bool is_sq(square s)
{
    return (s & 0x88) == 0;
}

// convert row and col to 0x88 square
inline square get_sq(int row, int col)
{
    return (row << 4) + col;
}

inline int sq_col(square s)
{
    return s & 7;
}

inline int sq_row(square s)
{
    return s >> 4;
}

// Check if string is valid algebraic coordinate
inline bool is_coord_valid(const std::string s)
{
    return (s.size() == 2 &&
            'a' <= s[0] && s[0] <= 'h' &&
            '1' <= s[1] && s[1] <= '8');
}

inline std::string write_sq(square s)
{
    assert(is_sq(s));
    char file = 'a' + sq_col(s);
    char rank = '1' + sq_row(s);
    return std::string {file, rank};

}

inline square sq_from_coord(const std::string coord)
{
    assert(is_coord_valid(coord));
    int row = coord[1] - '1';
    int col = coord[0] - 'a';
    return get_sq(row, col);
}



