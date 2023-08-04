#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iterator>
#pragma ONCE
#include "algo.h"
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
class Solution {
public:
  Solution() {}
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

  void lowercase(char start) {
    // convert all characters in c string to lowercasew with pointers;
    char *p = &start;
    while (*p != '\0') {
      if (*p >= 97 && *p <= 122) {
        *p -= 32;
      }
      p++;
    }
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
    while (temp->next != 0x0) {
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
    for (int k = 0; k < vals.size(); k++) {
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

  void removeclosestoccurences(char in) {
    // use pointer to a to increment and decrement for nearest occurences near
    // index in str of a assume input is a char* with "I am unwell\" \"We need
    // to go..." rewrite string with pointers
    char *src, *dest;
    src = dest = &in; // both pointers point to the first char of input
    while (*src != '\0' && src) // exit loop when null terminator reached
    {
      if (in != *src) // if source is not a " char
      {
        *dest = *src; // copy the char at source to destination
        dest++;       // increment destination pointer
      } else {
        dest++;
      }
      src++; // increment source pointer
    }
    *dest = '\0'; // terminate string with null terminator

    // input now contains "I am unwell We need to go..."
  }

  int minimizedStringLength(string s) {
    int size = s.size();
    for (int i = 0; i < size; i++) {
      removeclosestoccurences(s[i]);
    }
    return s.size();
  }

  string makeGood(string s) {
    std::stack<int> ans;
    string final(s.size(), ' '); // initialize string ans with size = s.size()
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

  void bubsort(string &unsorted) {
    for (int i = 0; i < unsorted.size(); i++) {
      for (int j = i + 1; j < unsorted.size(); j++) {
        if (unsorted[i] > unsorted[j]) {
          char t = unsorted[j];
          unsorted[j] = unsorted[i];
          unsorted[i] = t;
        }
      }
    }
  }

  void bubsort(vector<int> &unsorted) {
    for (int i = 0; i < unsorted.size(); i++) {
      for (int j = i + 1; j < unsorted.size(); j++) {
        if (unsorted[i] > unsorted[j]) {
          char t = unsorted[j];
          unsorted[j] = unsorted[i];
          unsorted[i] = t;
        }
      }
    }
  }

  vector<int> abs(vector<int> &nums) {
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] < 0) {
        ans.push_back(~nums[i] + 1);
      } else {
        continue;
      }
    }
    return ans;
  }

  void msort_char(vector<char> &unsorted, unsigned a, unsigned p, unsigned q) {
    // works so long as a<=p<q
    size_t n1 = p - a + 1;
    size_t n2 = q - p;
    size_t j = 0;
    size_t i = 0;
    vector<int> *L = new vector<int>(n1 + 1);
    vector<int> *R = new vector<int>(n2 + 1);
    if (a <= p && p < q) {
      for (; i < n1 && j < n2; i++ && j++) {
        L->at(i) = (unsorted[i + a - 1]);
        R->at(j) = (unsorted[j + p]);
      }
      L->at(n1) = CHAR_MAX;
      R->at(n2) = CHAR_MAX;
      i = j = 0;
      for (unsigned k = a; k < q && i < n1 && j < n2; k++) {
        if (L->at(i) <= R->at(j)) {
          unsorted[k] = L->at(i);
          i++;
        } else {
          unsorted[k] = R->at(j);
          j++;
        }
      }
    } else {
      cout << "FAILED INDICES" << std::endl;
    }
  }
  void msort(vector<int> &unsorted, unsigned a, unsigned p, unsigned q) {
    // works so long as a<=p<q
    size_t n1 = p - a + 1;
    size_t n2 = q - p;
    size_t i = 0;
    size_t j = 0;
    vector<int> *L = new vector<int>(n1 + 1);
    vector<int> *R = new vector<int>(n2 + 1);
    std::vector<int>::iterator L_ptr = L->begin();
    std::vector<int>::iterator R_ptr = R->begin();
    if (a <= p && p < q) {
      for (; L_ptr != --L->end() && R_ptr != --R->end(); i++ && j++) {
        *L_ptr = (unsorted[i + a]);
        *R_ptr = (unsorted[j + p + 1]);
        L_ptr++;
        R_ptr++;
      }
      L->at(n1) = INT_MAX;
      R->at(n2) = INT_MAX;
      i = j = 0;
      for (unsigned k = a; k < q && i < n1 && j < n2; k++) {
        if (L->at(i) <= R->at(j)) {
          unsorted[k] = L->at(i);
          i++;
        } else {
          unsorted[k] = R->at(j);
          j++;
        }
      }
    } else {
      cout << "FAILED INDICES" << std::endl;
    }
  }


  int findClosestNumber(vector<int> &nums) {
    // find closest number to 0 within an array of integers nums
    if (nums.size() == 0) {
      return 0;
    }
    size_t q = nums.size();
    size_t p = q / 2;
    vector<int> absolute = abs(nums);
    msort(absolute, 0, p, q);
    msort(nums, 0, p, q);
    if (absolute[0] != nums[0]) {
      // closest number to 0 is negative
      return nums[0];
    } else {
      return absolute[0];
    }
  }

private:

};