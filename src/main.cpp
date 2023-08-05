#include "../Algorithms/algo.hpp"
#include "../Algorithms/bits.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

  if (strcmp(argv[1], "string") == 0) {
    cout << "Enter your input below." << endl;
    string in;
    vector<char> invec;
    cin >> in;
    for (int i = 0; i < in.size(); i++) {
      invec.push_back(in[i]);
    }
    Solution *algo = new Solution();
    size_t size = sizeof(invec) / sizeof(invec[0]);
    algo->msort_char(invec, 0, (size / 2), invec.size());
    cout << "AFTER EXCAVATION:" << endl;
    for (int i = 0; i < invec.size(); i++) {
      cout << invec[i];
    }
    cout << endl;
  } else {
    cout << "No input given." << endl;
  }
}