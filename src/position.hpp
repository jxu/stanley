#include <array>
#include "board.hpp"

#pragma once

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