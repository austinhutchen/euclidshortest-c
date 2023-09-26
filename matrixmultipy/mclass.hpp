#pragma ONCE
#include <vector>
#include <iostream>
using namespace std;

class matrixrow {
  matrixrow(void) { row = new vector<int>(); }

  void fill(string in, unsigned start, size_t count) {
    for (int i = start; i < count; i++) {
      row->push_back(in[i]);
    }
  }

private:
  vector<int> *row;
};