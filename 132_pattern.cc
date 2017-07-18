#include <limits>
#include <vector>
#include "gtest/gtest.h"

class Solution {
public:
    bool find132pattern(const std::vector<int>& nums) {
        uint32_t n = nums.size();
        if (n < 3) {
            return false;
        }

        std::vector<int> left_larger_index(n, -1);
        std::vector<int> left_min_val(n);
        std::vector<int> index_queue{0};

        left_min_val[0] = std::numeric_limits<int>::max();
        for (uint32_t i = 0; i + 1 < n; ++i) {
            left_min_val[i + 1] =
                std::min(left_min_val[i], nums[i]);
            while (!index_queue.empty()) {
                int j = index_queue.back();
                if (nums[j] > nums[i + 1]) {
                    left_larger_index[i + 1] = j;
                    break;
                }
                index_queue.pop_back();
            }
            index_queue.push_back(i + 1);

            int kk = i + 1;
            int jj = left_larger_index[i + 1];
            if (jj != -1 && left_min_val[jj] < nums[kk]) {
                return true;
            }
        }

        return false;
    }
};

TEST(LeetCode, 132_Pattern)
{
    Solution solver;
    EXPECT_FALSE(solver.find132pattern({}));
    EXPECT_FALSE(solver.find132pattern({1, 1, 1}));
    EXPECT_FALSE(solver.find132pattern({1, 2, 3}));
    EXPECT_FALSE(solver.find132pattern({3, 2, 1}));
    EXPECT_TRUE(solver.find132pattern({1, 3, 2}));
    EXPECT_TRUE(solver.find132pattern({5, 1, 5, 5, 3, 5, 2}));
}
