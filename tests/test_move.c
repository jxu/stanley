#include "board.h"
#include "move.h"
#include "unity.h"

void test_move(void)
{
    char buf[10];
    buf[9] = 0;
    char* new_buf = write_coord(buf, sq_from_coord("e4"));
    TEST_ASSERT(buf[0] == 'e' && buf[1] == '4');
}
