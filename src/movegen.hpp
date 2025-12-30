#pragma once

#include <vector>
#include <array>
#include <cassert>
#include "move.hpp"

// 0x88 board directions
enum Direction : square
{
    NN = 16,
    EE = 1,
    SS = -16,
    WW = -1,
    NE = NN + EE,
    SE = SS + EE,
    SW = SS + WW,
    NW = NN + WW,
};

constexpr std::array<Direction, 4> DIRECTION_ROOK = {NN, EE, SS, WW};
constexpr std::array<Direction, 4> DIRECTION_BISHOP = {NE, SE, SW, NW};
constexpr std::array<Direction, 8> DIRECTION_QUEEN = {NN, EE, SS, WW, NE, SE, SW, NW};
constexpr auto DIRECTION_KING = DIRECTION_QUEEN;
constexpr std::array<square, 8> DIRECTION_KNIGHT =
    {NN+NE, NN+NW, EE+NE, EE+SE, SS+SE, SS+SW, WW+NW, WW+SW};

// TODO: fixed-size move list

// Generate attacked squares for pieces that have fixed movement
// Does not do legality or castling
inline std::vector<square> king_attacks(square sq)
{
    assert(is_valid(sq));
    std::vector<square> targets;
    for (const Direction d : DIRECTION_KING)
    {
        square target = sq + d;
        if (is_valid(target))
            targets.push_back(target);
    }
    return targets;
}

