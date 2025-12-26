#include <array>
#include "board.hpp"

#pragma once

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
    uint8_t castle_flags;
    square ep_target; // 0xFF to store none
    int halfmove;
    int fullmove;

    // Read fen is null-terminated FEN string
    Position(const std::string& fen);
};

const square NO_EP_TARGET = -1;

const std::string START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";