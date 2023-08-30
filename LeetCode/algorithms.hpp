#include <climits>
#include <cstdint>
#include <iterator>
#pragma ONCE
#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
#define nullptr __nullptr
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  Solution() {}
  bool searchKeyHelper(TreeNode *currNode, int targetSum, int *prevsum) {
    if (currNode == NULL)
      return 0;
    *prevsum += currNode->val;
    if (*prevsum == targetSum)
      return true;

    if (*prevsum > targetSum) {
      return searchKeyHelper(currNode->left, targetSum, prevsum);
    }

    return searchKeyHelper(currNode->right, targetSum, prevsum);
  }
  bool hasPathSum(TreeNode *root, int targetSum) {
    int val = 0;
    return searchKeyHelper(root, targetSum, &val);
  }

  bool searchMatrix(vector<vector<int> > &matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    int low = 0, high = n * m - 1, mid, row, col;
    while (low <= high) {
      mid = (low + high) / 2;
      row = mid / m; // getting the row number
      col = mid % m; // getting the column number
      if (matrix[row][col] == target)
        return true;
      else if (matrix[row][col] > target)
        high = mid - 1;
      else
        low = mid + 1;
    }
    return false;
  }

  int hammingWeight(unsigned n) {
    int counter = 0;
    while (n > 0) {
      if (n & 1) {
        ++counter;
      }
      n = n >> 1;
    }
    return counter;
  }

  vector<int> countBits(int n) {
    vector<int> ans(n + 1);
    std::iota(std::begin(ans), std::end(ans), 0);
    vector<int>::iterator p = ans.begin();
    vector<int>::iterator end = ans.end();
    for (; p != end; p++) {
      *p = hammingWeight(*p);
    }
    return ans;
  }

  uint32_t reverseBits(uint32_t n) {
    uint32_t ans;
    for (int i = 0; i < 32; i++) {
      ans = ans << 1;
      bool bit = n & 1;
      ans = ans | bit;
      n = n >> 1;
      // cout << bit << " ";
    }
    return ans;
  }

  ListNode *reverseList(ListNode *head) {
    if (head == NULL || head->next == NULL) {
      return head;
    }
    ListNode *curr, *prev, *next = 0x0;
    curr = head;
    prev = nullptr;
    while (curr != nullptr) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }

    return prev;
  }

  TreeNode *createNode(int val) { return new TreeNode(val); }

  TreeNode *sortedArrayToBST(vector<int> &nums) {

    // root would be lowest value in entire array
    if (nums.size() == 0) {
      return 0x0;
    }
    if (nums.size() == 1) {
      return createNode(nums[0]);
    } else {
      // split array into two pieces and create left and right branches
      vector<int> L(nums.begin(), nums.begin() + nums.size() / 2);
      vector<int> R(nums.begin() + nums.size() / 2 + 1, nums.end());
      TreeNode *root = createNode(nums[nums.size() / 2]);
      root->left = sortedArrayToBST(L);
      root->right = sortedArrayToBST(R);
      return root;
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

  void msort_itr(vector<char> &unsorted, unsigned a, unsigned p, unsigned q) {
    // works so long as a<=p<q
    size_t n1 = p - a + 1;
    size_t n2 = q - p;
    size_t i = 0;
    size_t j = 0;
    vector<int> *L = new vector<int>(n1 + 1);
    vector<int> *R = new vector<int>(n2 + 1);
    std::vector<int>::iterator L_ptr = L->begin();
    std::vector<int>::iterator R_ptr = R->begin();
    *L->end() = INT_MAX;
    *R->end() = INT_MAX;
    for (; L_ptr != L->end() && R_ptr != R->end(); i++ && j++) {
      *L_ptr = (unsorted[i + a]);
      *R_ptr = (unsorted[j + p + 1]);
      L_ptr++;
      R_ptr++;
    }
    i = j = 0;
    L_ptr = L->begin();
    R_ptr = R->begin();
    auto Rend = R->end();
    auto Lend = L->end();
    for (unsigned k = a; k < q && L_ptr != Lend && R_ptr != Rend; k++) {
      if (*L_ptr <= *R_ptr) {
        unsorted[k] = *L_ptr;
        L_ptr++;
      } else {
        unsorted[k] = *R_ptr;
        R_ptr++;
      }
    }
  }

  void msort(vector<int> &unsorted, unsigned a, unsigned p, unsigned q) {
    // works so long as a<=p<q
    size_t n1 = p - a + 1;
    size_t n2 = q - p;
    unsigned i = 0;
    unsigned j = 0;
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    for (; i < n1; i++) {
      L[i] = (unsorted[i + a]);
    }
    for (; j < n2; j++) {
      R[j] = (unsorted[j + p]);
    }
    R[n1] = INT_MAX;
    L[n2] = INT_MAX;
    i = j = 0;
    for (unsigned k = a; k < q && i < n1 && j < n2; k++) {
      if (L[i] <= R[j]) {
        unsorted[k] = L[i];
        i++;
      } else {
        unsorted[k] = R[j];
        j++;
      }
    }
  }

  int findClosestNumber(vector<int> &nums) {
    // find closest number to 0 within an array of integers nums
    switch (nums.size()) {
    case 0: {
      return 0;
      break;
    }
    case 1: {
      return nums[0];
      break;
    }
    default: {
      vector<int> absolute = abs(nums);
      msort(absolute, 0, (nums.size() - 1) / 2, nums.size() - 1);
      msort(nums, 0, (nums.size() - 1) / 2, nums.size() - 1);
      if (absolute[0] != nums[0]) {
        // closest number to 0 is negative
        return nums[0];
      } else {
        return absolute[0];
      }
    }
    }
  }

  int fib(int n) {
    if (n == 0 || n == 1) {
      return n;
    } else {
      n = fib(n - 1) + fib(n - 2);
    }
    return n;
  }

  bool strPal(string check) {
    std::stack<char> ans;
    int i = 0;
    for (; i < check.size(); i++) {
      ans.push(check[i]);
    }
    i = 0;
    while (!ans.empty()) {
      if (ans.top() == check[i]) {
        i++;
        ans.pop();
        continue;
      } else {
        return false;
      }
    }
    return true;
  }

  bool isPalindrome(ListNode *head) {
    if (head == NULL) {
      return true;
    }
    string result;
    ListNode *temp = head;
    while (temp != NULL) {
      result.push_back(char(temp->val));
      temp = temp->next;
    }
    return strPal(result);
  }

  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    // merge sorted array
    std::vector<int>::iterator L_ptr = nums1.begin();
    std::vector<int>::iterator R_ptr = nums2.begin();
    if (L_ptr == nums1.end() || R_ptr == nums2.end()) {
      return;
    }
    auto Lend = nums2.end();
    size_t size = nums1.size();
    unsigned i = m;
    for (unsigned k = 0; k < size && L_ptr != Lend && i < size; k++) {
      if (nums1[k] <= *L_ptr) {
        nums1[k] = *L_ptr;
        L_ptr++;
      }
      if (nums1[i] <= *R_ptr) {
        nums1[i] = *R_ptr;
        R_ptr++;
        i++;
      }
    }
    bubble(nums1);
  }

  void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
  }
  void swap(char *a, char *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
  }
  void bubble(vector<int> &unsorted) {
    for (int i = 0; i < unsorted.size(); i++) {
      for (int j = i + 1; j < unsorted.size(); j++) {
        if (unsorted[i] > unsorted[j]) {
          this->swap(&unsorted[i], &unsorted[j]);
        }
      }
    }
  }

  void lowercase(char &start) {
    // convert all characters in c string to lowercasew with pointers;
    char *p = &start;
    while (*p != '\0') {
      if (*p >= 97 && *p <= 122) {
        *p = tolower(*p);
      }
      p++;
    }
  }

  bool isomorphic(std::stack<char> stck, std::string string) {
    uint i = 0;
    while (!stck.empty()) {
      if (string[i] == stck.top()) {
        i++;
        stck.pop();
      } else {
        return false;
      }
    }
    return true;
  }

  void alphastr(string &check) {
    // does check have all alphanumeric characters?
    // alphanumeric characters lie in the ASCII value range of [65, 90] for
    // uppercase alphabets, [97, 122] for lowercase alphabets, and [48, 57] for
    // digits
    char *c = &check[0];
    for (; *c != '\0'; c++) {
      if (*c >= 65 && *c <= 90 || *c >= 97 && *c <= 122 ||
          *c >= 48 && *c <= 57) {
        // alphanumeric
        continue;
      } else {
        // will need to be changed to45t3y fully remove the nonalphanumeric
        // indices
        *c = ' ';
      }
    }
    return;
  }

  bool isPalindrome(string s) {
    // determine if string is a palindrome after removing non alphanumeric
    // characters from str
    if (s.size() == 0) {
      return false;
    }
    alphastr(s);
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    lowercase(s[0]);
    std::stack<char> nums;
    for (int i = 0; i < s.size(); i++) {
      nums.push(s[i]);
    }
    return isomorphic(nums, s);
  }

  int majorityElement(vector<int> &nums) {
    uint sz = nums.size();
    if (sz == 1) {
      return nums[0];
    }
    for (vector<int>::iterator p = nums.begin(); p != nums.end(); p++) {
      uint counter = 1;
      for (vector<int>::iterator i = nums.begin(); i != nums.end(); i++) {
        if (*i == *p && p != i) {
          counter++;
        }
      }
      if (counter > sz / 2) {
        return *p;
      }
    }
    return 0x0;
  }

  void moveZeroes(vector<int> &nums) {
    std::queue<int> ordered;
    for (vector<int>::iterator i = nums.begin(); i != nums.end(); i++) {
      if (*i == 0) {
        continue;
      } else {
        ordered.push(*i);
      }
    }
    uint sz = ordered.size();
    uint i = 0;
    while (!ordered.empty()) {
      nums[i] = ordered.front();
      ordered.pop();
      i++;
    }
    for (; i < nums.size(); i++) {
      nums[i] = 0;
    }
    return;
  }

  bool isSubsequence(string s, string t) {

    if (s.size() == 0) {
      return true;
    }
    if (s.size() > t.size() || s != t && s.size() == t.size() ||
        t.size() == 0) {
      return false;
    }
    std::stack<char> stck;
    for (int i = s.size() - 1; i >= 0; i--) {
      stck.push(s[i]);
    }
    for (int i = 0; i < t.size(); i++) {
      if (!stck.empty() && stck.top() == t[i]) {
        stck.pop();
      }
      if (stck.empty()) {
        return true;
      }
    }
    return false;
  }

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
          swap(&unsorted[i], &unsorted[j]);
        }
      }
    }
  }
  string gcdOfStrings(string str1, string str2) {
    // attempt 2
    std::queue<string> gcd;
    if (str1 == str2) {
      return str1;
    }
    for (int i = 0; i < str1.size(); i++) {
      std::string ans;
      for (int k = 0; k < str2.size(); k++) {
        uint j = i;
        uint m = k;
        while (str1[j] == str2[m]) {
          ans += str1[j];
          j++;
          m++;
        }
        // string is now a common divisor
        gcd.push(ans);
      }
    }
    int max = INT_MIN;
    string temp;
    while (!gcd.empty()) {
      uint sz = gcd.front().size();
      if (sz > max) {
        temp = gcd.front();
        max = sz;
      }
      gcd.pop();
    }
    return temp;
  }
  bool isUgly(int n) {
    if (n == 0 || n == 1) {
      return false;
    }
    bool ans = n % 2 || n % 3 || n % 5;
    for (int i = 1; i < n / 2; i++) {
      if (n % i == 0 && i != 2 && i != 3 && i != 5) {
        return false;
      }
    }
    return true;
  }

  bool isBadVersion(int i) { return true; }
  int firstBadVersion(int n) {
    if (n == 1)
      return n;

    int low = 1, high = n;
    while (low < high) {
      int mid = low + (high - low) / 2;
      if (isBadVersion(mid))
        high = mid;
      else
        low = mid + 1;
    }
    return low;
  }
  bool isPowerOfThree(int n) {
    if (n == 0) {
      return false;
    }
    if (n == 1) {
      return true;
    }
    int max = cbrt(n);
    if (n % 3 == 0) {
      // all powers of 3 are divisible by 3
      for (int i = 1; i <= max; i++) {
        if (pow(3, i) == n) {
          return true;
        }
      }
    }
    return false;
  }
  bool isPowerOfFour(int n) {
    if (n == 0) {
      return false;
    }
    if (n == 1) {
      return true;
    }
    float max = pow(n, 0.5);
    if (n % 4 == 0) {
      // all powers of 3 are divisible by 3
      for (int i = 1; i <= max; i++) {
        if (pow(4, i) == n) {
          return true;
        }
      }
    }
    return false;
  }
  class NumArray {
  public:
    vector<int> ans;
    NumArray(vector<int> &nums) {
      for (int i = 0; i < nums.size(); i++) {
        ans.push_back(nums[i]);
      }
    }

    int sumRange(int left, int right) {
      uint sum = 0;
      auto p = &ans.at(left);
      auto end = &ans.at(right);
      while (p != end) {
        sum += *p;
        p++;
      }
      return sum;
    }
    /**
     * Definition for singly-linked list.
     * struct ListNode {
     *     int val;
     *     ListNode *next;
     *     ListNode(int x) : val(x), next(NULL) {}
     * };
     */
    class Solution {
    public:
      int length(ListNode *head) {
        int len = 0;
        while (head) {
          len++;
          head = head->next;
        }
        return len;
      }
      int max(unsigned int1, unsigned int2) {
        if (int1 > int2) {
          return int1;
        } else {
          return int2;
        }
      }
      ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *t1 = headA;
        ListNode *t2 = headB;
        std::vector<int> sol;
        if (!headA || !headB) {
          return 0x0;
        }
        int len1 = length(t1);
        int len2 = length(t2);
        if (max(len1, len2) == len1) {
          while (len1 > len2) {
            t1 = t1->next;
            len1--;
          }
        }

        else if (max(len1, len2) == len2) {
          while (len2 > len1) {
            t2 = t2->next;
            len2--;
          }
        }
        while (t1 && t2) {
          // heads are not synced for search
          if (t1 == t2) {
            return t1;
          }
          t1 = t1->next;
          t2 = t2->next;
        }
        return 0x0;
      }
    }; /**
        * Definition for singly-linked list.
        * struct ListNode {
        *     int val;
        *     ListNode *next;
        *     ListNode(int x) : val(x), next(NULL) {}
        * };
        */

    int length(ListNode *head) {
      int len = 0;
      while (head) {
        len++;
        head = head->next;
      }
      return len;
    }
    int max(unsigned int1, unsigned int2) {
      if (int1 > int2) {
        return int1;
      } else {
        return int2;
      }
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
      // find where LLA and LLB intersect
      ListNode *t1 = headA;
      ListNode *t2 = headB;
      std::vector<int> sol;
      if (!headA || !headB) {
        return 0x0;
      }
      int len1 = length(t1);
      int len2 = length(t2);
      if (max(len1, len2) == len1) {
        while (len1 > len2) {
          t1 = t1->next;
          len1--;
        }
      }

      else if (max(len1, len2) == len2) {
        while (len2 > len1) {
          t2 = t2->next;
          len2--;
        }
      }
      while (t1 && t2) {
        // heads are not synced for search
        if (t1 == t2) {
          return t1;
        }
        t1 = t1->next;
        t2 = t2->next;
      }
      return 0x0;
    }
  };
};
