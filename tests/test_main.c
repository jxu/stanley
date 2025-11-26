#include "unity.h"

// unity functions
void setUp(void) {}
void tearDown(void) {}


extern void test_board();
extern void test_fen();
extern void test_move();

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_board);
    RUN_TEST(test_fen);
    RUN_TEST(test_move);
    return UNITY_END();
}
