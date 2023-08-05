#include "../Algorithms/algo.hpp"
#include "../Algorithms/bits.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  string in;
  vector<char> invec;
  Solution *algo = new Solution();
  if (argv[1]) {
    in = argv[1];
  } else {
    cout << "Enter your input below." << endl;
    cin >> in;
  }
  for (int i = 0; i < in.size(); i++) {
    invec.push_back(in[i]);
  }
  int middle= int((invec.size()) / 2)-1;
  algo->msort_char(invec, 0, middle, invec.size()-1);
  cout << "AFTER EXCAVATION:" << endl;
  for (int i = 0; i < invec.size(); i++) {
    cout << invec[i];
  }
  cout << endl;
}