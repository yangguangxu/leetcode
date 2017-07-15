#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "gtest/gtest.h"
#include "glog/logging.h"

class Solution 
{
public:
    std::vector<int> towSum(std::vector<int>& nums, int target) 
    {
        std::unordered_map<int, int> value_index;
        for (uint32_t i = 0; i < nums.size(); ++i) {
            auto diff = target - nums[i];
            auto it = value_index.find(diff);
            if (it != value_index.end()) {
                return {it->second, static_cast<int>(i)};
            }
            value_index[nums[i]] = i;
        }
        return {};
    }
};

TEST(LeetCode, Tow_Sum) 
{
    Solution solver;
    auto check = [&solver](
        const std::vector<int>& input, int target,
        const std::vector<int>& output) {
        auto mutable_input = input;
        EXPECT_EQ(solver.towSum(mutable_input, target), output);
    };

    check({}, 0, {});
    check({1}, 0, {});
    check({1, 2}, 3, {0, 1});
    check({3, 7, 2, 1}, 10, {0, 1});
    check({3, 7, 2, 1}, 0, {});
}
