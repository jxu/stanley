#include "unity.h"

// unity functions
void setUp(void) {}
void tearDown(void) {}


void test_board();

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_board);
    return UNITY_END();
}
