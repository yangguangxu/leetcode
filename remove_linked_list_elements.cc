#include <vector>
#include "gtest/gtest.h"

namespace {

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        while (head && head->val == val) {
            auto next = head->next;
            delete head;
            head = next;
        }
        if (!head) {
            return head;
        }

        auto p = head;
        while (p->next) {
            if (p->next->val == val) {
                auto q = p->next->next;
                delete p->next;
                p->next = q;
            } else {
                p = p->next;
            }
        }

        return head;
    }
};

// util function for unit test
ListNode* ToList(const std::vector<int>& elems)
{
    if (elems.empty()) {
        return nullptr;
    }
    ListNode* head = new ListNode(elems.front());
    ListNode* prev = head;
    for (uint32_t i = 1; i < elems.size(); ++i) {
        prev->next = new ListNode(elems[i]); 
        prev = prev->next;
    }
    return head;
}

std::vector<int> ToVector(ListNode* elems)
{
    if (!elems) {
        return {};
    }
    std::vector<int> vec;
    while (elems) {
        vec.push_back(elems->val);
        elems = elems->next;
    }
    return vec;
}

std::vector<int> Remove(const std::vector<int>& elems, int val)
{
    Solution solver;
    auto res = solver.removeElements(ToList(elems), val);
    return ToVector(res);
}

std::vector<int> Wrap(const std::vector<int>& vals)
{
    return vals;
}

}

TEST(LeetCode, Remote_Linked_List_Elements)
{
    Solution solver;
    EXPECT_EQ(Remove({}, 0), Wrap({}));
    EXPECT_EQ(Remove({1}, 1), Wrap({}));
    EXPECT_EQ(Remove({1}, 2), Wrap({1}));
    EXPECT_EQ(Remove({1, 1, 1}, 1), Wrap({}));
    EXPECT_EQ(Remove({1, 1, 1, 2, 3, 1, 4, 1}, 1), Wrap({2, 3, 4}));
}
