#include <algorithm>

#include "doctest.h"
#include "movegen.hpp"

inline void check_squarelist(const std::vector<square>& actual, const std::vector<square>& ref)
{
    auto actual_sorted = actual;
    std::sort(actual_sorted.begin(), actual_sorted.end());
    CHECK_EQ(actual_sorted, ref);
}


TEST_CASE("movegen")
{
    check_squarelist(king_attacks(D4), std::vector<square>{C3, D3, E3});
}