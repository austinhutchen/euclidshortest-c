#include <cstdlib>
#include <sys/_types/_size_t.h>
#pragma ONCE
#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

struct coordinate {
  // x is a vector in R^2
  coordinate(const char *x1) {
    x[0] = atof(x1);
    f1 = true;
  }
  coordinate(){

  }
  void setcoord1(const char *x1) {
    x[0] = atof(x1);
    f1 = true;
  }
  void setcoord2(const char *x1) {
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
  double distance(coordinate *c) {
    // Calculating distance from the coordinate at c
    return sqrt(pow(this->x[1] - this->x[0], 2) +
                pow(c->x0() - c->x1(), 2) * 1.0);
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

        if (nums[cr][cc]->x0() >= nums[nr][nc]->x0() && nums[cr][cc]->x1() > nums[nr][nc]->x1() ) {
          swap(&nums[cr][cc],
               &nums[nr][nc]); // any way you want to swap variables
        }
      }
    }
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
                  coordinate *p = 0x0;
          for (char *i = &line[0]; *i != '#'; i++) {
            string flt;
              
            while (*i <= '9' && *i >= '0' || *i == '.') {
              // float read
              flt += char(*i);
              i++;
            }
            switch (*i) {
            case '{': {
              // open bracket
              cout << "starting bracket reached .." << endl;
              p= new coordinate();
              break;
            }
            // close bracket;
            case ',': {
              // comma
              alphastr(flt);
              const char *buffer = flt.c_str();
              p->setcoord1(buffer);
              flt = "";
              break;
            }
            case '}': {
              alphastr(flt);
              const char *buffer = flt.c_str();
              // buffer is too big
              p->setcoord2(buffer);
               if(p->isfull())
               {
                counter++;
                flt = "";
              // closing bracket
              points[x] = p;
              x++;
              break;
              };
             
            }
            case ' ': {
              // ignore whitespaces
              break;
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

  double min = 0.0;
  std::stack<coordinate *> MINSTACK;
  // in progress
  void MIN(coordinate *coord, double distance, std::stack<coordinate *> stck) {
    if (distance < min) {
      stck.push(coord);
    }
  }
  // vector forms the rows of the two-dimensional euclidian plane
  // coordinate ** represents a single line in the euclidian plane from left to
  // right to look up or down, observe the respective row of nums and compare to
  // MIN()
  coordinate *closestpair(vector<coordinate **> nums) {
    // temp is used to measure distance from our current coordinate within nums
    // temp is FIXED and thus only other coordinates will be returned
    coordinate *temp;
    #pragma omp parallel for
    for (int i = nums.size() / 2; i < nums.size(); i++) {
      int k = 0;
      temp = nums[i][k];
      // find a way to implement minimum function
      if (temp->distance(nums[i][k + 1]) < min) {
        MIN(nums[i][k + 1], temp->distance(nums[i][k + 1]), MINSTACK);
      }

      k++;
    }
    for (int j = nums.size() / 2; j > 0; j--) {
      int k = 0;
      temp = nums[j][k];
      // find a way to implement minimum function
      if (temp->distance(nums[j][k + 1])< min) {
        MIN(nums[j][k + 1], temp->distance(nums[j][k + 1]), MINSTACK);
      }
    }
    // temp used for nearest pair of points
    // return the pair as nums
    // sort nums
    // should now be sorted in terms of euclidian plane
    // split nums into left and right halves using algorithm
    return MINSTACK.top();
  }
};
