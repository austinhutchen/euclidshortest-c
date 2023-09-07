#include <cstdlib>
#pragma ONCE
#include <fstream>
#include <iostream>

using namespace std;

struct coordinate {
  float x1;
  float x2;
  coordinate(int x3, int x4) {
    x1 = x3;
    x2 = x4;
  }
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
  double *numparse(string in) {
    // start AFTER first bracket

    int index = 1;
    ifstream f;
    const char *ind;
    f.open(in);
    vector<vector<double> > nums;
    string line;
    if (f.good()) {
      vector<double> buffarr;
      while (getline(f, line)) {
        buffarr.clear();
        string flt;
        for (char *i = &line[0]; *i != '#'; i++) {

          while (char(*i) <= 9) {

            // float read
            flt += *i;
            i++;
          }
          const char *buffer = flt.c_str();
          if ((int(*i)) > 9) {
            double answer = atof(buffer);
            // nums.push_back(strtod(&flt[0], &flt));
            buffarr.push_back(answer);
          }
        }
        nums.push_back(buffarr);
      }
      // parse the vector here for an implementation of
      return closestpair(nums);
    }
    return 0x0;
  }

  double *closestpair(vector<vector<double> > nums) {
    // determine closest pair of points in plane represented by distance
    // function
    double vals[] = {0, 0};
    coordinate *current = new coordinate(0, 0);
    // return the pair as nums
    // sort nums
    twoDimBubbleSort(nums, 0, 0);
    // should now be sorted in terms of euclidian plane
    for (int i = 0; i < nums.size(); i++) {


    }
    return vals;
  }
  void swap(double *a, double *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
  }
  void twoDimBubbleSort(vector<vector<double> > nums, int row, int col) {
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
