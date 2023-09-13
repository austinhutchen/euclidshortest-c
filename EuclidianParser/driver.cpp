
#include "./code/EuclidianArithmetic.hpp"
#include <iterator>
std::stack<coordinate *> MINSTACK;
double minim = 0xff;

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
void sort1D(vector<coordinate *> arr) {
  // consider x1 as 0 for all coordinates and sort only based on x0
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (arr[i] != 0x0 && arr[j] != 0x0) {
        if (arr[i]->x0() > arr[j]->x0() && i != j) {
          swap(arr[i], arr[j]);
        }

        if (arr[i]->x0() == arr[j]->x0() && i != j) {
          arr[i]->x1() > arr[j]->x1() ? swap(arr[i], arr[j]) : donothing();
        }
      }
    }
  }
}

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
  // change into binary search?
  for (unsigned x = 1; x < nums.size(); x++) {
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

void printplane(vector<coordinate *> R) {
  for (int i = 0; i < R.size(); i++) {
    R[i]->printcoords();
  }
}
class Comparex {
public:
  bool operator()(coordinate *e1, coordinate *e2) {
    return e1->x0() < e2->x0(); // strict weak ordering required
  }
};

class Comparey {
public:
  bool operator()(coordinate *e1, coordinate *e2) {
    return e1->x1() < e2->x1(); // strict weak ordering required
  }
};
int main(int argc, char **argv) {
  PlaneArithmetic *inst = new PlaneArithmetic();
  char **t = argv;
  if (t[1] != nullptr) {
    vector<coordinate *> array = inst->filein(t[1]);
    if (array.empty()) {
      cout << "EMPTY" << endl;
      return -1;
    } else {
      // two dimensional sort
      std::stable_sort(array.begin(), array.end(), Comparey());
      std::stable_sort(array.begin(), array.end(), Comparex());
      printplane(array);
      closestdistance(array);
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
