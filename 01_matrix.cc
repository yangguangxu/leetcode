#include <vector>
#include <queue>
#include "gtest/gtest.h"

class Solution {
public:
    std::vector<std::vector<int>> updateMatrix(const std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix.front().empty()) {
            return {};
        }

        uint32_t n = matrix.size();
        uint32_t m = matrix.front().size();
        std::vector<std::vector<int>> dist(n, std::vector<int>(m, 2 * (n + m)));
        std::queue<std::pair<int, int>> q;
        for (uint32_t i = 0; i < n; ++i) {
            for (uint32_t j = 0; j < m; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        std::vector<std::pair<int, int>> step_option
        {
            {0, 1}, {1, 0}, {-1, 0}, {0, -1}
        };

        while (!q.empty()) {
            auto pos = q.front();
            q.pop();
            int32_t i = pos.first;
            int32_t j = pos.second;
            for (const auto& one_step : step_option) {
                int32_t ni = i + one_step.first;
                int32_t nj = j + one_step.second;
                if (0 <= ni && ni < n && 0 <= nj && nj < m
                    && dist[ni][nj] > dist[i][j] + 1) {
                    dist[ni][nj] = dist[i][j] + 1;
                    q.push({ni, nj});
                }
            }
        }

        return dist;
    }
};

std::vector<std::vector<int>> Wrap(const std::vector<std::vector<int>>& vals)
{
    return vals;
}

TEST(LeetCode, Zero_One_Maxtrix)
{
    Solution solver;
    EXPECT_EQ(
    solver.updateMatrix(
        {{0, 0, 0},
         {0, 1, 0},
         {0, 0, 0}}), 
    Wrap(
        {{0, 0, 0},
         {0, 1, 0},
         {0, 0, 0}})); 

    EXPECT_EQ(
    solver.updateMatrix(
        {{0, 0, 0},
         {0, 1, 0},
         {1, 1, 1}}),
    Wrap(
       {{0, 0, 0},
        {0, 1, 0},
        {1, 2, 1}}));
}
