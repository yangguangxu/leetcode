#include <string>
#include <vector>
#include "gtest/gtest.h"

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        int32_t n = s.size();
        int32_t m = p.size();
        std::vector<bool> flag;
        std::string merged_p;
        for (int32_t i = 0; i < m;) {
            if (i + 1 < m && p[i + 1] == '*') {
                flag.push_back(true);
                i += 2;
            } else {
                flag.push_back(false);
                i += 1;
            }
            merged_p.push_back(p[i]);
        }
        m = merged_p.size();

        std::vector<std::vector<bool>> match(
            n + 1, std::vector<bool>(m + 1, false));

        match[n][m] = true;
        for (int32_t j = m - 1; 0 <= j; ++j) {
            match[n][j] = (flag[j] && match[n][j + 1]);
        }

        for (int32_t i = n - 1; 0 <= i; --i) {
            for (int32_t j = m - 1; 0 <= j; --j) {
                if (flag[j]) {
                    if (merged_p[j] == '.' || merged_p[j] == s[i]) {
                        match[i][j] = (
                            match[i + 1][j] || match[i][j + 1] || match[i + 1][j + 1]);
                    }
                } else {
                    match[i][j] = (
                        (merged_p[j] == '.' || merged_p[j] == s[i])
                        && match[i + 1][j + 1]);
                }
            }
        }

        return match[0][0];
    }
};

TEST(LeetCode, Regular_Expression_Match)
{
    Solution solver;
    EXPECT_TRUE(solver.isMatch("", ""));
    EXPECT_TRUE(solver.isMatch("aaaa", "aaaa"));
    EXPECT_FALSE(solver.isMatch("", "aaaa"));
    EXPECT_FALSE(solver.isMatch("aaaa", ""));
    EXPECT_TRUE(solver.isMatch("", "a*"));
    EXPECT_TRUE(solver.isMatch("", ".*"));
    EXPECT_TRUE(solver.isMatch("", "a*"));
    EXPECT_TRUE(solver.isMatch("", "a*b*.*"));
    EXPECT_TRUE(solver.isMatch("aaabb", "a*b*"));
    EXPECT_TRUE(solver.isMatch("aaabb", "a*.*"));
    EXPECT_TRUE(solver.isMatch("aaabb", "d*a*b*"));
    EXPECT_TRUE(solver.isMatch("aaabb", "d*a*.*"));
}
