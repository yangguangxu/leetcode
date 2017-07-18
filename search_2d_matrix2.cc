#include <vector>
#include "glog/logging.h"
#include "gtest/gtest.h"

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix.front().empty()) {
            return false;
        }

        mat_ = &matrix;
        target_ = target;

        int32_t n = matrix.size();
        int32_t m = matrix.front().size();

        return RecursiveSearch(0, n, 0, m);
    }

private:
    bool RecursiveSearch(int32_t row_begin, int32_t row_end,
                         int32_t col_begin, int32_t col_end) {

        if (row_begin >= row_end ||
            col_begin >= col_end) {
            return false;
        }

        if (row_begin + 1 == row_end &&
            col_begin + 1 == col_end) {
            return target_ == (*mat_)[row_begin][col_begin];
        }

        int row_mid = (row_begin + row_end) >> 1;
        int col_mid = (col_begin + col_end) >> 1;
        int diff =  target_ - (*mat_)[row_mid][col_mid];

        // LOG(INFO) << "(" << row_begin << ", " << col_begin << ")"
        //        << " (" << row_end << ", " << col_end << " diff: " << diff;

        if (diff == 0) {
            return true;
        } else if (diff < 0) {
            return RecursiveSearch(row_begin, row_mid, col_begin, col_mid) ||
                   RecursiveSearch(row_mid, row_end, col_begin, col_mid) ||
                   RecursiveSearch(row_begin, row_mid, col_mid, col_end);
        } else {
            return RecursiveSearch(row_mid, row_end, col_begin, col_mid) ||
                   RecursiveSearch(row_begin, row_mid, col_mid, col_end) ||
                   RecursiveSearch(row_mid, row_end, col_mid, col_end);
        }
    }

    std::vector<std::vector<int>>* mat_;
    int target_;
};

TEST(LeetCode, Search_2D_Matrix2)
{
    Solution solver;
    std::vector<std::vector<int>> mat = 
    {
        {1,   4,  7, 11, 15},
        {2,   5,  8, 12, 19},
        {3,   6,  9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

    EXPECT_TRUE(solver.searchMatrix(mat, 1));

    for (const auto& row : mat) {
        for (const auto& val : row) {
            EXPECT_TRUE(solver.searchMatrix(mat, val));
        }
    }

    for (const auto& val : {-1, 0, 31, 32}) {
        EXPECT_FALSE(solver.searchMatrix(mat, val));
    }
}
