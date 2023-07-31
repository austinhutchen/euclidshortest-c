#include <cstddef>
#include <ctime>
#pragma ONCE
#include "algo.h"
#include <chrono>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
class Solution {
public:
  Solution() { start = time(NULL); }
  vector<int> removeDuplicates(vector<int> &nums) {
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
    return ans;
  }

  int removeDuplicatesconstant(vector<int> &nums) {
    // bubble sort method
    int index = 1;
    // sorts using a fixed in-place variable index that iterates up to store
    // non-duplicates
    for (int y = 1; y < nums.size(); y++) {
      if (nums[y] != nums[y - 1]) {
        nums[index] = nums[y];
        index++;
      }
    }
    return index;
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

  void deletenode(ListNode *head, int val) {
    if (head == 0x0) {
      return;
    }
    ListNode *temp = head;
    ListNode *prev = temp;
    while (prev != 0x0 && temp->val != val) {
      prev = temp;
      temp = temp->next;
    }

    prev->next = temp->next;
    delete temp;
    temp = 0x0;
    return;
  }

  void populate(ListNode *head, std::vector<int> &vals) {
    ListNode *temp = head;
    while (temp && temp->next) {
      vals.push_back(temp->val);
      temp = temp->next;
    }
    return;
  }

  ListNode *deleteDuplicates(ListNode *head) {
    if (head == 0x0) {
      return 0x0;
    }
    std::vector<int> vals;
    populate(head, vals);
    int src = removeDuplicatesconstant(vals);
    for (int k = src; k < vals.size(); k++) {
      // duplicates to remove in LL
      deletenode(head, vals[k - 1]);
    }
    return head;
  }

  string restoreString(string s, vector<int> &indices) {
    string ans(s.size(), '.');
    for (int i = 0; i < s.size(); i++) {
      ans[indices[i]] = s[i];
    }
    return ans;
  }

  void removeclosestoccurences(char a) {
    // use pointer to a to increment and decrement for nearest occurences
    // assume input is a char* with "I am unwell\" \"We need to go..."
    // rewrite string with pointers
    char *src, *dest;
    src = dest = &a;     // both pointers point to the first char of input
    while (*src != '\0') // exit loop when null terminator reached
    {
      if (*src != '\"') // if source is not a " char
      {
        *dest = *src; // copy the char at source to destination
        dest++;       // increment destination pointer
      }
      src++; // increment source pointer
    }
    *dest = '\0'; // terminate string with null terminator

    // input now contains "I am unwell We need to go..."
  }

  int minimizedStringLength(string s) {
    for (int i = 0; i < s.size(); i++) {
      // removeclosestoccurences(s[i]);
    }
    return s.size();
  }

  string makeGood(string s) {
    std::stack<int> ans;
    string final(s.size(), 'a'); // initialize string ans with size = s.size()
                                 // and all char of it as 'a'
    short int prev;
    for (int i = 0; i < s.size(); i++) {
      ans.push(s[i]);
    }
    while (ans.top()) {
      if (ans.top() == prev + 32 || ans.top() == prev - 32) {
        // dont add these to new string;
        continue;
      } else {
        final.push_back(ans.top());
      }
      prev = ans.top();
      ans.pop();
    }
    return final;
  }

private:
  time_t start;
  time_t usrtime = start - time(NULL);
};