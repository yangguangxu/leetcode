#include <string>
#include <bitset>
#include "gtest/gtest.h"

class Solution 
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        std::bitset<256> exists;
        int max_length = 0;
        int i = 0, j = 0;

        // loop invirant: keep character in s[i, j) unique
        while (j < s.size()) {
            if (!exists.test(s[j])) {
                exists.set(s[j]);
            } else {
                while (i < j && s[i] != s[j]) {
                    exists.reset(s[i++]);
                }
                ++i;
            }
            ++j;
            max_length = std::max(j - i, max_length);
        }

        return max_length;
    }
};

TEST(LeetCode, Longest_String_Without_Repeating_Characters)
{
    Solution solver;
    EXPECT_EQ(solver.lengthOfLongestSubstring(""), 0);
    EXPECT_EQ(solver.lengthOfLongestSubstring("aaaa"), 1);
    EXPECT_EQ(solver.lengthOfLongestSubstring("ababa"), 2);
    EXPECT_EQ(solver.lengthOfLongestSubstring("abcbcda"), 4);
}
