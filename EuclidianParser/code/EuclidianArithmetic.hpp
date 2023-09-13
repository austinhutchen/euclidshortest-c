#include <cstdlib>
#include <string>
#include <system_error>
#pragma ONCE
#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

class coordinate {
public:
  // x is a vector in R^2
  coordinate(void) {
    x = new long double[2]();
    x[0]=x[1]=0.0;
  }
  void setcoord(double x1, double x2) {
    x[0] = x1;
    x[1] = x2;
  }
  double x0(void) { return x[0]; }
  double x1(void) { return x[1]; }

  double distance(coordinate *c) {
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
// Assignment 1
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
  void printvec(vector<coordinate **> nums) {
    for (int i = 0; i < nums.size(); i++) {
      coordinate *p = nums[i][0];
      unsigned short counter = 0;
      do {
        if (p != 0x0) {
          p->printcoords();
          p += sizeof(coordinate);
          counter++;
        }
      } while (counter < 10);
    }
    cout << endl;
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
    i = p;
    try {
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
          switch (*i) {
          case '{': {
            // change code to use i while newline character isnt reached to
            // recursively call numparse on sets of coordinates
            if (*i != '\n') {
              coordinate *p = new coordinate();
              p->setcoord(numparse(line, i), numparse(line, i));
              points->push_back(p);
            }
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
          // nums.push_back(points);
          // float parse
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
