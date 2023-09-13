
#include "./code/EuclidianArithmetic.hpp"
#include <algorithm>
#include <iterator>

std::stack<coordinate *> MINSTACK;
double minim = 1.7976931348623157E+308;

void MIN(coordinate *coord, double distance, std::stack<coordinate *> stck) {
  if (distance < minim) {
    minim = distance;
    stck.push(coord);
  }
}

void swap(coordinate *a, coordinate *b) {
  coordinate temp = *b;
  *b = *a;
  *a = temp;
}
void donothing() {}
// in progress
// vector forms the rows of the two-dimensional euclidian plane
// coordinate ** represents a single line in the euclidian plane from left to
// right to look up or down, observe the respective row of nums and compare to
// MIN()
void closestdistance(vector<coordinate *> nums) {
  // take distance between all pairs using described algorithm splitting list
  // into left and right after origin sort furthest distance should be between
  // points on opposite end of splitted array
  coordinate *p = 0x0;
  coordinate *R = 0x0;
  coordinate *L = 0x0;
  // split the array along our line at p, and then break array into left and right sets to recursively solve
  for (unsigned x = 1; x + 1 < nums.size(); x++) {
    p = nums[x];
    R = nums[x + 1];
    L = nums[x - 1];
    if (R == 0x0) {
      return;
    }
    // unsure why this does not work
    if (p != 0x0) {
      p->distance(R) < minim ? minim = p->distance(R) : minim = minim;
      p->distance(L) < minim ? minim = p->distance(L) : minim = minim;
    }
  }
}

// temp used for nearest pair of points
// return the pair as nums
// sort nums
// should now be sorted in terms of euclidian plane
// split nums into left and right halves using algorithm

void empty(void) {
  while (!MINSTACK.empty()) {
    MINSTACK.pop();
  }
}
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
      empty();

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
