#pragma ONCE
#include "parser.hpp"
#include <iostream>
#include <vector>
using namespace std;

class matrixrow {
  matrixrow(void) { row = new vector<int>(); }
  matrixrow(unsigned size) { row = new vector<int>(size); }

  void fill(string in, unsigned start, size_t count) {
    parser *p = new parser();
    for (int i = start; i < count; i++) {
      row->push_back(in[i]);
    }
  }

private:
  vector<int> *row;
};