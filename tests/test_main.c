#include "unity.h"

// unity functions
void setUp(void) {}
void tearDown(void) {}


void test_board();
void test_fen();

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_board);
    RUN_TEST(test_fen);
    return UNITY_END();
}
