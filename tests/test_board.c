#include <assert.h>
#include "board.h"

void test_board(void) 
{
    assert(is_black(-KING));
    assert(!is_black(KNIGHT));

    assert(get_sq(1, 2) == 0x12);

    assert(is_sq(0x00));
    assert(is_sq(0x77));
    assert(!is_sq(0x80));
    assert(!is_sq(-1)); // casts to square

    assert(sq_col(0x54) == 4);
    assert(sq_row(0x54) == 5);

    assert(!is_coord_valid(""));
    assert(!is_coord_valid("a0"));
    assert(is_coord_valid("b2"));

    assert(sq_from_coord("a1") == 0x00);
    assert(sq_from_coord("h6") == 0x57);

    printf("Test board passed\n");
}
