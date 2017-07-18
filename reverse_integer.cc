#include <cmath>
#include <limits>
#include "gtest/gtest.h"

class Solution {
public:
    int reverse(int x) {
       bool sign = x < 0;
       x = ::abs(x);

       int64_t x_reversed = 0;
       while (x) {
           int32_t digit = x % 10;
           x /= 10;
           x_reversed = 10 * x_reversed + digit;
       }
       x_reversed = sign ? -x_reversed : x_reversed;
       return x_reversed <= std::numeric_limits<int32_t>::max() &&
              x_reversed >= std::numeric_limits<int32_t>::min() ?
              static_cast<int32_t>(x_reversed) : 0;
    }
};

TEST(LeetCode, Reverse_Integer)
{
    Solution solver;
    EXPECT_EQ(solver.reverse(0), 0);
    EXPECT_EQ(solver.reverse(1), 1);
    EXPECT_EQ(solver.reverse(3333), 3333);
    EXPECT_EQ(solver.reverse(-123), -321);
    EXPECT_EQ(solver.reverse(-123), -321);
    EXPECT_EQ(solver.reverse(1234567899), 0);
}
