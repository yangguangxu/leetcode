#include <vector>
#include "gtest/gtest.h"

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1 || !l2)
            return l1 ? l1 : l2;

        ListNode* head = nullptr;
        ListNode* prev = nullptr;
        int accumulator = 0;
        while (l1 || l2 || accumulator) {
            accumulator += (l1 ? l1->val : 0);
            accumulator += (l2 ? l2->val : 0);

            ListNode* cur = new ListNode(accumulator % 10);
            if (!head) {
                head = cur;
            } else {
                prev->next = cur;
            }

            prev = cur;
            accumulator /= 10;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        return head;
    }
};

// util functions for unit test
ListNode* ToList(uint64_t val) {
    ListNode* head = new ListNode(val % 10);
    ListNode* prev = head;
    while (val /= 10) {
        prev->next = new ListNode(val % 10);
        prev = prev->next;
    }
    return head;
}

uint64_t ToUint64(ListNode* l) {
    uint64_t val = 0;
    uint64_t power = 1;
    while (l) {
        val += power * l->val;
        power *= 10;
        l = l->next;
    }
    return val;
}

uint64_t Add(uint64_t a, uint64_t b) {
    Solution solver;
    ListNode* res = solver.addTwoNumbers(ToList(a), ToList(b));
    return ToUint64(res);
}

TEST(LeetCode, Add_Two_Numbers) {
    EXPECT_EQ(Add(0, 0), 0);
    EXPECT_EQ(Add(1, 5), 6);
    EXPECT_EQ(Add(99995, 5), 100000);
}
