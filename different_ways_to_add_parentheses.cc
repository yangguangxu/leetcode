#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "gtest/gtest.h"
#include "glog/logging.h"

enum TokenType
{
    kVal,
    kAdd,
    kSub,
    kMul
};

struct Token
{
    TokenType type;
    int32_t val;
    Token(TokenType t_type, int32_t t_val):
         type(t_type), val(t_val) {}
};

class Solution {
public:
    std::vector<int> diffWaysToCompute(std::string input)
    {
        std::vector<Token> tokens;
        Parse(input, &tokens);
        auto res = GetAllPossibleResults(0, tokens.size(), tokens);
        std::sort(res.begin(), res.end());
        old_results_.clear();
        return res;
    }

private:
    std::unordered_map<uint64_t, std::vector<int>> old_results_;

    std::vector<int> GetAllPossibleResults(
        uint32_t l, uint32_t r, const std::vector<Token>& tokens)
    {

        if (l == r) return {};

        auto key = (static_cast<uint64_t>(l) << 32) | r;
        auto it = old_results_.find(key);
        if (it != old_results_.end()) {
            return it->second;
        }

        assert(tokens[l].type == kVal);
        assert(tokens[r - 1].type == kVal);

        if (l + 1 == r) {
            return {tokens[l].val};
        }

        std::vector<int> res;
        for (uint32_t i = l + 1; i < r; i += 2) {
            assert(tokens[i].type != kVal);
            auto left_res = GetAllPossibleResults(l, i, tokens);
            auto right_res = GetAllPossibleResults(i + 1, r, tokens);
            for (const auto& left_val : left_res) {
                for (const auto& right_val : right_res) {
                    switch (tokens[i].type) {
                        case kAdd: res.push_back(left_val + right_val); break;
                        case kSub: res.push_back(left_val - right_val); break;
                        case kMul: res.push_back(left_val * right_val); break;
                    }
                }
            }
        }

        old_results_.insert({key, res});
        return res;
    }

    void Parse(const std::string& expr, std::vector<Token>* tokens)
    {
        // 0 for operator
        // 1 for positive number
        // 2 for negative number
        int32_t parse_val = 0;
        int32_t val = 0;
        for (uint32_t i = 0; i < expr.size(); ++i) {
            if (!i) {
                if (expr[i] == '-') {
                    parse_val = 2;
                    val = 0;
                } else {
                    parse_val = 1;
                    val = expr[i] - '0';
                }
            } else {
                auto ch = expr[i];
                if (!('0' <= ch && ch <= '9')) {
                    tokens->push_back(Token{kVal, val});
                    TokenType op;
                    switch (ch) {
                        case '+': op = kAdd; break;
                        case '-': op = kSub; break;
                        case '*': op = kMul; break;
                    }
                    tokens->push_back({op, 0});
                    parse_val = 1;
                    val = 0;
                } else {
                    int32_t digit = ch - '0';
                    val = 10 * val + (parse_val == 1 ? digit : -digit);
                }
            }
        }
        tokens->emplace_back(kVal, val);
    }
};

// util funtion for test
std::vector<int> Wrap(const std::vector<int>& vals) {
    return vals;
}

TEST(LeetCode, Different_Ways_To_Add_Parenthese)
{
    Solution solver;
    EXPECT_EQ(solver.diffWaysToCompute("2-1-1"), Wrap({0, 2}));
    EXPECT_EQ(solver.diffWaysToCompute("2*3-4*5"), Wrap({-34, -14, -10, -10, 10}));
}
