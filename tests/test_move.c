#include "board.h"
#include "move.h"
#include "unity.h"

void test_move(void)
{
    char buf[10];

    Move move = 
    {
        .from = sq_from_coord("d2"),
        .to = sq_from_coord("d4"),
        .promotion = NIL
    };

    // overwrite buf with d2d4 move
    write_move(buf, move);
    TEST_ASSERT_EQUAL_STRING_LEN("d2d4", buf, 4);

    Move move_promo = 
    {
        .from = sq_from_coord("e7"),
        .to = sq_from_coord("e8"),
        .promotion = QUEEN,
    };

    write_move(buf, move_promo);
    TEST_ASSERT_EQUAL_STRING_LEN("e7e8q", buf, 5);
}
