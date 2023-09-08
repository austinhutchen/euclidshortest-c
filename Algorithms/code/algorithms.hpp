#include <cstdlib>
#include <sys/_types/_size_t.h>
#pragma ONCE
#include <fstream>
#include <iostream>

using namespace std;

struct coordinate {
  // x is a vector in R^2

  coordinate(const char *x1) {
    x[0] = atof(x1);
    f1 = true;
  }
  void setcoord(const char *x1) {
    x[1] = atof(x1);
    f2 = true;
  }
  double x0(void) { return x[0]; }
  double x1(void) { return x[1]; }
  bool isfull(void) {
    if (f1 && f2) {
      return true;
    }
    return false;
  }
  float distance(float y1, float y2) {
    // Calculating distance from y1 and y2
    return sqrt(pow(this->x[1] - this->x[0], 2) + pow(y2 - y1, 2) * 1.0);
  }
  void printcoords(void) {
    cout << "( " << *x << " , " << *(x + 8) << " )" << endl;
  }

private:
  bool f1, f2;
  double x[2];
  size_t size;
};
// Assignment 1
class PlaneArithmetic {
public:
  // HELPERS
  char *find(string str, char a, int start) {
    char *t = &str[start];
    while (t != '\0') {
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
  void swap(coordinate **a, coordinate **b) {
    coordinate *temp = *b;
    *b = *a;
    *a = temp;
  }
  // adjust for sorting by coordinates
  void twoDimBubbleSort(vector<coordinate **> nums, int row, int col) {
    // REALLY inefficient but is easy to read
    for (int i = 0; i < (row * col); ++i) {
      for (int j = 0; j < (row * col) - 1; ++j) {
        int cr = j / col;       // current row
        int cc = j % col;       // current column
        int nr = (j + 1) / col; // next item row
        int nc = (j + 1) % col; // next item column

        if (nums[cr][cc]->x0() > nums[nr][nc]->x0()) {
          swap(&nums[cr][cc],
               &nums[nr][nc]); // any way you want to swap variables
        }
      }
    }
  }
  // END HELPERS
  //  - -- - --- -- - - - - - - -- - -------------------->               FOR
  //  CECS            < ------ - - - - - - - - - -- - - - - -- - - -
  void numparse(string in) {

    // start AFTER first bracket

    ifstream f;
    const char *ind;
    f.open(in);
    // vector of rows of arrays of max size 20 representing coordinates
    vector<coordinate **> nums;
    string line;
    // array of "window" of coordinate pointers being compared at a time
    // max of 10 pairs of points per line.
    coordinate *points[10] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    unsigned x = 0;
    unsigned counter;
    if (!f.fail()) {
      while (getline(f, line)) {
        if (!line.empty()) {
          counter = 0;
          for (char *i = &line[1]; *i != '#'; i++) {
            string flt;
            while (*i <= '9' && *i >= '0') {
              // float read
              flt += char(*i);
              i++;
            }
            coordinate *p = 0x0;
            switch (*i) {
            case '{': {
              // open bracket
              cout << "starting bracket reached .." << endl;
              break;
            }
            // close bracket;
            case ',': {
              // comma
              const char *buffer = flt.c_str();
              p = new coordinate(buffer);
              flt = "";
              break;
            }
            case '}': {
              const char *buffer = flt.c_str();
              p->setcoord(buffer);
              if (p->isfull()) {
                counter++;
              }
              flt = "";
              // closing bracket
              points[x] = p;
              x++;
              break;
            }
            case ' ': {
              break;
            }
            case '.': {
              cout << "DECIMAL FOUND" << endl;
            }
            default: {
              cout << *i << "  {IN BUFFER} " << endl;
              break;
            }
              // will insert newline char at end of string
              // double answer = atof(buffer);
              //  temp.push_back(buffer)
              // each point in array represents a pair of coordinates
            }
            // nums.push_back(points);
            nums.push_back(points);
          }
          // float parse
        }
        printvec(nums);
        // asdfsd
        return;
      }
    }
  }

  double *closestpair(vector<coordinate **> nums) {
    // determine closest pair of points in plane represented by distance
    // function
    double temp[] = {0.0, 0.0};
    // temp used for nearest pair of points
    // return the pair as nums
    // sort nums
    // should now be sorted in terms of euclidian plane
    // split nums into left and right halves using algorithm
    return temp;
  }
};
