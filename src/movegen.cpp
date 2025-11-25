#include "move.hpp"
#include <vector>

enum Direction
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

constexpr std::array<int, 4> DIRECTION_ROOK = {{NN, EE, SS, WW}};
constexpr std::array<int, 4> DIRECTION_BISHOP = {NE, SE, SW, NW};
constexpr std::array<int, 8> DIRECTION_QUEEN = 
    {NN, EE, SS, WW, NE, SE, SW, NW};

// to optimize later to fixed size
std::vector<Move> generate_slider(const Position& pos, const square sq, 
                                  const std::array<int, 8> directions);

