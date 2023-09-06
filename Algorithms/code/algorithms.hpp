#pragma ONCE
#include <fstream>
#include <iostream>

using namespace std;

struct coordinate {
  float x1;
  float x2;
  void setcoords(double x1, double x2) {
    this->x1 = x1;
    this->x2 = x2;
  }
  float distance(float y1, float y2) {
    // Calculating distance from y1 and y2
    return sqrt(pow(this->x2 - this->x1, 2) + pow(y2 - y1, 2) * 1.0);
  }
};
// Assignment 1
class PlaneArithmetic {
public:
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

  // for CECS
  int numparse(string in) {
    // start AFTER first bracket

    int index = 1;
    ifstream f;
    const char *ind;
    f.open(in);
    vector<vector<double> > nums;
    string line;
    coordinate *current = new coordinate();
    if (f.good()) {
      while (getline(f, line)) {
        string flt;
        for (char *i = &line[0]; *i != ','; i++) {
          while (int(*i) <= 9) {

            // float read
            flt += *i;
            i++;
          }
          if ((int(*i)) > 9) {
            // nums.push_back(strtod(&flt[0], &flt));
          }
        }
      }
    }
  }

  int closestpair(vector<vector<int> > nums) {
    // determine closest pair of points in plane represented by distance
    // function
    // sort nums
    twoDimBubbleSort(nums, 0, 0);
    // should now be sorted in terms of euclidian plane
    for (int i = 0; i < nums.size(); i++) {
    }
  }
  void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
  }
  void twoDimBubbleSort(vector<vector<int> > nums, int row, int col) {
    // REALLY inefficient but is easy to read
    for (int i = 0; i < (row * col); ++i) {
      for (int j = 0; j < (row * col) - 1; ++j) {
        int cr = j / col;       // current row
        int cc = j % col;       // current column
        int nr = (j + 1) / col; // next item row
        int nc = (j + 1) % col; // next item column

        if (nums[cr][cc] > nums[nr][nc])
          this->swap(&nums[cr][cc],
                     &nums[nr][nc]); // any way you want to swap variables
      }
    }
  }
};
