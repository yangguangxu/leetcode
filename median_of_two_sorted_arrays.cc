#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "glog/logging.h"

class Solution {
public:
    // basice thought: use binary search to find postion of median merged point
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        if (nums1.empty())
            return findMedian(nums2);
        if (nums2.empty())
            return findMedian(nums1);

        if (nums1.size() > nums2.size())
            nums1.swap(nums2);

        size_t n = nums1.size() + nums2.size();
        size_t k = (n >> 1) + 1;
        bool has_odd_elems = n & 1;

        LOG(INFO) << "n: " << n << " k: " << k;

        if (k - 1 < nums1.size() && nums1[k - 1] <= nums2.front()) {
            if (has_odd_elems)
                return nums1[k - 1];
            else
                return (nums1[k - 2] + nums1[k - 1]) / 2.0;
        }
        if (k - 1 < nums2.size() && nums2[k - 1] <= nums1.front()) {
            if (has_odd_elems)
                return nums2[k - 1];
            else
                return (nums2[k - 2] + nums2[k - 1]) / 2.0;
        }

        int32_t pos1 = -1;
        uint32_t l = 0, r = std::min(nums1.size() - 1, k - 1);
        while (l < r) {
            uint32_t i = (l + r) >> 1;
            uint32_t j = k - (i + 1) - 1;
            LOG(INFO) << " l: " << l << " r: " << r
                      << " i: " << i << " j: " << j;
            if (j >= nums2.size()) {
                l = i + 1;
            } else {
                auto guess_val = std::max(nums1[i], nums2[j]);
                LOG(INFO) << " guess_val: " << guess_val;
                if ( (i + 1 < nums1.size() && nums1[i + 1] < guess_val) ||
                     (j + 1 < nums2.size() && nums2[j + 1] < guess_val) ) {
                    if (nums1[i] >= nums2[j])
                        r = i - 1;
                    else
                        l = i + 1;
                }
                else {
                    pos1 = i;
                    break;
                }
            }
        }
        if (pos1 == -1)
            pos1 = l;

        int32_t pos2 = k - (pos1 + 1) - 1;
        if (has_odd_elems)
            return std::max(nums1[pos1], nums2[pos2]);
        else {
            std::vector<int> elems;
            elems.push_back(nums1[pos1]);
            elems.push_back(nums2[pos2]);
            if (pos1 - 1 >= 0)
                elems.push_back(nums1[pos1 - 1]);
            if (pos2 - 1 >= 0)
                elems.push_back(nums2[pos2 - 1]);
            std::sort(elems.begin(), elems.end());

            LOG(INFO) << " pos1: " << pos1 << " pos2: " << pos2;
            for (const auto& elem : elems)
                LOG(INFO) << "elem: " << elem;

            double right = elems.back();
            elems.pop_back();
            double left = elems.back();
            return (left + right) / 2.0;
        }
    }

private:
    double findMedian(const std::vector<int>& nums) 
    {
        if (nums.empty())
            return 0.0;
        auto n = nums.size();
        return n & 1 ? nums[(n + 1) / 2 - 1] :
            (nums[n / 2 - 1] + nums[n / 2]) / 2.0;
    }
};

TEST(LeetCode, Median_Of_Two_Sorted_Arrays)
{
    auto med =
    [](const std::vector<int>& nums1,
       const std::vector<int>& nums2) {
        Solution solver;
        auto mutable_nums1 = nums1;
        auto mutable_nums2 = nums2;
        return solver.findMedianSortedArrays(
            mutable_nums1, mutable_nums2);
    };

    EXPECT_NEAR(med({}, {}), 0.0, 0.000001);
    EXPECT_NEAR(med({1}, {}), 1.0, 0.000001);
    EXPECT_NEAR(med({}, {1}), 1.0, 0.000001);
    EXPECT_NEAR(med({1, 2}, {}), 1.5, 0.000001);
    EXPECT_NEAR(med({}, {1, 2}), 1.5, 0.000001);
    EXPECT_NEAR(med({3, 4, 5}, {1, 2}), 3.0, 0.000001);
    EXPECT_NEAR(med({1, 2, 3, 4, 5}, {6, 7}), 4.0, 0.000001);
    EXPECT_NEAR(med({1, 3, 5, 7}, {2, 4, 6, 8}), 4.5, 0.000001);
    EXPECT_NEAR(med({1}, {2, 3, 4}), 2.5, 0.000001);
}
