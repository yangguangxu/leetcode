#include <vector>
#include <bitset>
#include <algorithm>
#include "gtest/gtest.h"

// util function for unit test
void Print(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

class Solution {
public:
    Solution():
        row_bit_map_(9, 0),
        col_bit_map_(9, 0),
        box_bit_map_(9, 0),
        rest_(1<<9), pos_(81){
        for (uint32_t bits = 0; bits < (1<<9); ++bits) {
            for (uint8_t num = 0; num < 9; ++num) {
                if (bits & (1<<num)) {
                    rest_[bits].push_back(num);
                }
            }
        }
    }

    void solveSudoku(std::vector<std::vector<char>>& board) {
        if (board.size() != 9 || board.front().size() != 9) {
            return ;
        }
        board_.swap(board);

        Clear();
        num_row = board_.size();
        num_col = board_.front().size();
        for (uint8_t row = 0; row < num_row; ++row) {
            for (uint8_t col = 0; col < num_col; ++col) {
                if (board_[row][col] == '.') {
                    pos_.push_back((row << 4) + col);
                    continue;
                }
                int bit_mask = 1 << (board_[row][col] - '1');
                for (auto ptr : {&row_bit_map_[row],
                    &col_bit_map_[col], &box_bit_map_[row / 3 * 3 + col / 3]}) {
                    if ( (*ptr) & bit_mask) {
                        *ptr ^= bit_mask;
                    }
                }
            }
        }

        Search();
        board_.swap(board);
    }

private:
    uint32_t num_row, num_col;
    std::vector<std::vector<char>> board_;
    std::vector<int> row_bit_map_;
    std::vector<int> col_bit_map_;
    std::vector<int> box_bit_map_;
    std::vector<std::vector<uint8_t>> rest_;
    std::vector<uint8_t> pos_; 

    void Clear()
    {
        row_bit_map_.clear();
        row_bit_map_.resize(9, 0x1ff);
        col_bit_map_.clear();
        col_bit_map_.resize(9, 0x1ff);
        box_bit_map_.clear();
        box_bit_map_.resize(9, 0x1ff);
        pos_.clear();
    }

    bool Search()
    {
        if (pos_.empty()) {
            return true;
        }

        //Print(board_);

        size_t min_count = 10;
        uint8_t min_row;
        uint8_t min_col;
        int min_mask;
        int min_index;

        // std::cerr << "pos_.size() = " << pos_.size() << std::endl;

        for (uint32_t i = 0; i < pos_.size(); ++i) { 
            auto pos = pos_[i];
            uint8_t row = (pos >> 4);
            uint8_t col = pos & 0xf;
            int bit_mask =
                row_bit_map_[row] &
                col_bit_map_[col] &
                box_bit_map_[row / 3 * 3 + col / 3];
            size_t count = rest_[bit_mask].size();
            /*
            std::cerr << "row:" << (int)row
                << " col:" << (int)col << " count: "
                << count << " mask:" << std::bitset<9>(bit_mask) << std::endl;
            */
            if (!count) {
                return false;
            }
            if (count < min_count) {
                min_count = count;
                min_row = row;
                min_col = col;
                min_mask = bit_mask;
                min_index = i;
            }
        }
        assert(min_count < 10);

        std::swap(pos_[min_index], pos_.back());
        pos_.pop_back();

        for (const auto& num : rest_[min_mask]) {
            assert(board_[min_row][min_col] == '.');
            int bit_mask = 1 << num;
            board_[min_row][min_col] = '1' + num;
            row_bit_map_[min_row] ^= bit_mask;
            col_bit_map_[min_col] ^= bit_mask;
            box_bit_map_[min_row / 3 * 3 + min_col / 3] ^= bit_mask;

            if (Search()) return true;

            row_bit_map_[min_row] ^= bit_mask;
            col_bit_map_[min_col] ^= bit_mask;
            box_bit_map_[min_row / 3 * 3 + min_col / 3] ^= bit_mask;
            board_[min_row][min_col] = '.';
        }

        pos_.push_back((min_row << 4) + min_col);
        std::swap(pos_[min_index], pos_.back());
        
        return false;
    }
};

bool IsValid(const std::vector<std::vector<char>>& board)
{
    Print(board);

    if (board.size() != 9 || board[0].size() != 9) {
        return false;
    }

    std::vector<int> row_mask(9, 0);
    std::vector<int> col_mask(9, 0);
    std::vector<int> box_mask(9, 0);
    for (uint8_t row = 0; row < board.size(); ++row) {
        for (uint8_t col = 0; col < board[0].size(); ++col) {
            auto ch = board[row][col];
            if (!('1' <= ch && ch <= '9')) {
                return false;
            }
            uint8_t num = ch - '1';
            int bit_mask = 1 << num;
            for (int* p : {&row_mask[row], &col_mask[col],
                &box_mask[row / 3 * 3 + col / 3]}) {
                if (*p & bit_mask) return false;
                *p |= bit_mask;
            }
        }
    }
    return true;
}

TEST(LeetCode, Sudoku_Solver)
{
    std::vector<std::vector<char>> input = 
    { 
      {'.','.','9','7','4','8','.','.','.'},
      {'7','.','.','.','.','.','.','.','.'},
      {'.','2','.','1','.','9','.','.','.'},
      {'.','.','7','.','.','.','2','4','.'},
      {'.','6','4','.','1','.','5','9','.'},
      {'.','9','8','.','.','.','3','.','.'},
      {'.','.','.','8','.','3','.','2','.'},
      {'.','.','.','.','.','.','.','.','6'},
      {'.','.','.','2','7','5','9','.','.'}
    };
    Solution solver;
    solver.solveSudoku(input);
    EXPECT_TRUE(IsValid(input));
}
