#pragma ONCE
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
class Solution {
public:
  int removeDuplicates(vector<int> &nums) {
    // use queue and loop through entire array??
    std::queue<int> q;
    vector<int> ans;
    int fix = 0;
    while (fix < nums.size()) {
      bool flag = false;
      q.push(nums[fix]);
      for (int i = fix + 1; i < nums.size(); i++) {
        if (q.front() == nums[i]) {
          // duplicate, needs to be removed from vector
          flag = true;
          break;
        }
      }
      if (flag != true) {
        // is NOT a duplicate
        // take out of queue
        q.pop();
        ans.push_back(nums[fix]);
        fix++;
      } else {
        // IS a duplicate, dont add to ans, leave in queue
        continue;
      }
    }
    return ans.size();
  }

  int removeDuplicatesconstant(vector<int> &nums) {
    // bubble up unique integers in numsß using fixed index iterator
    int index = 0;
    for (int y = 1; y < nums.size(); y++) {
      if (nums[y] != nums[y - 1]) {
        nums[index + 1] = nums[y];
        index++;
      }
    }
    return index + 1;
  }
  int removeElement(vector<int> &nums, int val) {
    // bubble up unique integers in numsß using fixed index iterator
    int k = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == val) {
        // start point for search on rest of elements in array
        nums.erase(nums.begin() + i);
      } else {
        k++;
      }
    }
    return k;
  }
  struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
  void deletenode(ListNode *head, int val) {
    ListNode *temp = head;
    ListNode *prev = 0x0;
    while (temp->val != val) {
      prev = temp;
      temp = temp->next;
    }
    prev->next = temp->next;
    delete temp;
    temp = 0x0;
    return;
  }
  ListNode *deleteDuplicates(ListNode *head) {
    // use stack in future
    std::vector<int> vals;
    ListNode *temp = head;
    while (temp != NULL) {
      vals.push_back(temp->val);
      temp = temp->next;
    }
    int src = removeDuplicatesconstant(vals);
    for (int k = src; k < vals.size(); k++) {
      // duplicates to remove in LL
      deletenode(head, vals[k]);
    }
    return head;
  }

private:
  time_t *usrtime;
};