#include "doctest.h"
#include "board.hpp"

TEST_CASE("board functions")
{
    CHECK(get_color(WKING) == WHITE);
    CHECK(get_color(BKNIGHT) == BLACK);
    CHECK(get_color(EMPTY) == NEUTRAL);

    CHECK(invert_color(WHITE) == BLACK);

    CHECK(invert_piece(WKING) == BKING);

    CHECK(get_sq(1, 2) == 0x12);

    CHECK(get_type(WKING) == KING);
    CHECK(get_type(BKNIGHT) == KNIGHT);

    CHECK(is_valid(0x00));
    CHECK(is_valid(0x77));
    CHECK(!is_valid(0x80));
    CHECK(!is_valid(-1)); // casts to square

    CHECK(sq_col(0x54) == 4);
    CHECK(sq_row(0x54) == 5);

    CHECK(!is_coord_valid(""));
    CHECK(!is_coord_valid("a0"));
    CHECK(!is_coord_valid("i2"));
    CHECK(is_coord_valid("b2"));

    CHECK(sq_from_coord("a1") == 0x00);
    CHECK(sq_from_coord("h6") == 0x57);

    CHECK(write_sq(0x34) == "e4");
}

