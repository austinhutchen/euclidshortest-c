
#include "./code/EuclidianArithmetic.hpp"
#include <algorithm>
#include <iterator>

double minim = 1.7976931348623157E+308;

void MIN(coordinate *coord, double distance, std::stack<coordinate *> stck) {
  if (distance < minim) {
    minim = distance;
  }
}

void swap(coordinate *a, coordinate *b) {
  coordinate temp = *b;
  *b = *a;
  *a = temp;
}
void donothing(void) {}
// in progress
// vector forms the rows of the two-dimensional euclidian plane
// coordinate ** represents a single line in the euclidian plane from left to
// right to look up or down, observe the respective row of nums and compare to
// MIN()

void copyvecL(vector<coordinate *> src, vector<coordinate *> &dest,
              vector<coordinate *>::iterator end) {
  std::vector<coordinate *>::iterator p = src.begin();
  unsigned counter = 0;
  while (p != end) {
    dest[counter] = (*p);
    counter++;
    p++;
  }
  return;
}
void copyvecR(vector<coordinate *> src, vector<coordinate *> &dest,
              vector<coordinate *>::const_iterator end) {
  std::vector<coordinate *>::iterator p = src.begin() + src.size() / 2;
  unsigned counter = 0;
  while (p != end) {
    dest[counter] = (*p);
    p++;
  }
  return;
}

void closestdistance(vector<coordinate *> nums) {
  // take distance between all pairs using described algorithm splitting list
  // into left and right after origin sort furthest distance should be between
  // points on opposite end of splitted array
  vector<coordinate *> *R = new vector<coordinate *>(nums.size() / 2 - 1);
  vector<coordinate *> *L = new vector<coordinate *>(nums.size() / 2 - 1);

  coordinate *p = nums[nums.size() / 2];
  copyvecL(nums, *L, nums.begin() + nums.size() / 2);

  copyvecR(nums, *R, nums.end());

  // split the array along our line at p, and then break array into left and
  // right sets to recursively solve might not work for all cases because we
  // have converted 2d coordinates to 1d. will need to fix this

  vector<coordinate *>::iterator r_itr = R->begin();
  vector<coordinate *>::iterator l_itr = L->begin();
  for (unsigned x = 0; x < nums.size() / 2; x++) {
    p->distance(*r_itr) < minim ? minim = p->distance(*r_itr) : minim = minim;
    p->distance(*l_itr) < minim ? minim = p->distance(*l_itr) : minim = minim;
    r_itr++;
    l_itr++;
  }
}

// temp used for nearest pair of points
// return the pair as nums
// sort nums
// should now be sorted in terms of euclidian plane
// split nums into left and right halves using algorithm

bool less(coordinate *a, coordinate *b) {
  return a->x0() < b->x0() || (a->x0() == b->x0() && a->x1() < b->x1());
}
void printplane(vector<coordinate *> R) {
  for (int i = 0; i < R.size(); i++) {
    R[i]->printcoords();
  }
}
class Compare {
public:
  // a is less than b operator, used for sort in R^2
  bool operator()(coordinate *a, coordinate *b) {
    return a->x0() < b->x0() || (a->x0() == b->x0() && a->x1() < b->x1());
  }
};

int main(int argc, char **argv) {
  PlaneArithmetic *inst = new PlaneArithmetic();
  char **t = argv;
  if (t[1] != nullptr) {
    vector<coordinate *> *array = inst->filein(t[1]);
    if (array->empty()) {
      cout << "EMPTY" << endl;
      return -1;
    } else {
      // split array into two equal subsets;
      std::sort(array->begin(), array->end(), Compare());
      printplane(*array);
      closestdistance(*array);
      cout << minim << " is shortest distance" << endl;
      cout << "=END=" << endl;
      return 1;
    }
  } else {
    cout << "INVALID FILENAME" << endl;
    return -1;
  }
  //  array set to array of points, now design sort below
  //  fix below
  /*
    printplane(array);
  coordinate *ans = closestpair(array);
  */

  // array of numbers is now set, now for sorting and
  // good parse
}
