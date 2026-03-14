#include "board.hpp"
#include "move.hpp"
#include "doctest.h"

TEST_CASE("move")
{
    auto move_e4 = Move(E2, E4);
    CHECK(move_e4.from == sq_from_coord("e2"));
    CHECK(move_e4.to == sq_from_coord("e4"));
    CHECK(move_e4.to_string() == "e2e4");

    auto promo = Move(sq_from_coord("a7"), sq_from_coord("a8"));
    promo.promotion = QUEEN;
    CHECK(promo.to_string() == "a7a8q");
}

