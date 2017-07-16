#include <string>
#include <vector>
#include "gtest/gtest.h"

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        if (s.size() < 2)
            return s.substr(0, 1);

        auto pos = [](uint32_t i, uint32_t j) {
            return (j + 1) * j / 2 + i;
        };

        uint32_t n = s.length();
        std::vector<bool> is_palin(n * (n + 1) / 2, false);

        for (uint32_t i = 0; i < n; ++i) {
            is_palin[pos(i, i)] = true;
            is_palin[pos(i, i + 1)] = true;
        }

        uint32_t max_length = 1;
        uint32_t begin = 0, end = 1;
        for (uint32_t d = 2; d <= n; ++d) {
            for (uint32_t i = 0; i + d <= n; ++i) {
                uint32_t j = i + d;
                is_palin[pos(i, j)] = 
                    (s[i] == s[j - 1] && is_palin[pos(i + 1, j - 1)]);

                if (is_palin[pos(i, j)] && d > max_length) {
                    max_length = d;
                    begin = i;
                    end = j;
                }
            }
        }

        return s.substr(begin, end - begin);
    }
};

TEST(LeetCode, Longest_Palindrome)
{
    Solution solver; 
    EXPECT_EQ(solver.longestPalindrome(""), "");
    EXPECT_EQ(solver.longestPalindrome("a"), "a");
    EXPECT_EQ(solver.longestPalindrome("ab"), "a");
    EXPECT_EQ(solver.longestPalindrome("aa"), "aa");
    EXPECT_EQ(solver.longestPalindrome("abccbd"), "bccb");
    EXPECT_EQ(solver.longestPalindrome("abccba"), "abccba");
    std::string s = "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth";
    solver.longestPalindrome(s);
}
