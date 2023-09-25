#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stack>
#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>
using namespace std;
#pragma ONCE
// will be used for strassen's algorithm implementation
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
class coordinate {
public:
  // x is a vector in R^2
  coordinate(void) {
    x = new long double[2]();
    x[0] = x[1] = 0.0;
  }
  void setcoord(long double x1, long double x2) {
    x[0] = x1;
    x[1] = x2;
  }
  long double x0(void) { return x[0]; }
  long double x1(void) { return x[1]; }

  long double distance(coordinate *c) {
    // Calculating distance from the coordinate at c
    return sqrt(pow(x[0] - c->x0(), 2) * 1.0 + pow(x[1] - c->x1(), 2) * 1.0);
  }
  void printcoords(void) {
    cout << "( " << x[0];
    cout << " , " << x[1] << " )" << endl;
  }

private:
  long double *x;
};

class PlaneArithmetic {
public:
  // HELPERS
  char *find(string str, char a, int start) {
    char *t = &str[start];
    while (*t != '\0') {
      if (*t == a) {
        return t;
      }
      t++;
    }
    return nullptr;
  }

  // adjust for sorting by coordinates

  long double numparse(string line, char *&i) {
    string ans = string();
    char *p = i;
    // run away from non numeric characters
    while (!(*p <= '9' && *p >= '0' || *p == '.')) {
      p++;
    }
    // start adding into double
    while ((*p <= '9' && *p >= '0') || *p == '.') {
      ans += *p;
      p++;
    }
    // i is now at next number index

    if (ans == "1" || ans == "0") {
      i = p;
      return -1;
    }
    try {
      i = p;
      return stold(ans);
    } catch (errc) {
      cout << "error converting" << endl;
      exit(0);
    }
  }

  // END HELPERS
  //  - -- - --- -- - - - - - - -- - -------------------->               FOR
  //  CECS            < ------ - - - - - - - - - -- - - - - -- - - -
  vector<coordinate *> *filein(string in) {
    // start AFTER first bracket
    ifstream f;
    f.open(in);
    // vector of rows of arrays of max size 20 representing coordinates
    string line;
    // array of "window" of coordinate pointers being compared at a time
    // max of 10 pairs of points per line.
    if (!f.fail()) {
      // allocate on the heap, dealing with large collections of numbers
      vector<coordinate *> *points = new vector<coordinate *>();
      while (getline(f, line, '\n')) {
        if (!line.empty()) {
          // 9 is first number
          char *i = &line[0];
          // MAIN PROGRAM
          while (i < &line[line.size() - 1]) {
            switch (*i) {
            case '{': {
              // change code to use i while newline character isnt reached to
              // recursively call numparse on sets of coordinates
              i++;
              coordinate *p = new coordinate();
              double x1 = numparse(line, *&i);
              double x2 = numparse(line, *&i);
              if (x1 == -1 && x2 == -1) {
                return points;
              }
              p->setcoord(x1, x2);
              points->push_back(p);

              break;
            }

            default: {
              break;
            }
              // will insert newline char at end of string
              // double answer = atof(buffer);
              //  temp.push_back(buffer)
              // each point in array represents a pair of coordinates
            }
            i++;
            // nums.push_back(points);
            // float parse
          }
        }
      }
      return points;
    } else {
      cout << "ERROR reading from file. Please check your spelling and "
              "placement of filename within this directory."
           << endl;
      return new vector<coordinate *>();
      ;
    }
  }
};
