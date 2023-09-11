
#include "./code/EuclidianArithmetic.hpp"
#include <iterator>
std::stack<coordinate *> MINSTACK;
double minim = 0.0;
void MIN(coordinate *coord, double distance, std::stack<coordinate *> stck) {
  if (distance < minim) {
    stck.push(coord);
  }
}

void swap(coordinate *a, coordinate *b) {
  coordinate temp = *b;
  *b = *a;
  *a = temp;
}
void planesort(coordinate **nums, int col) {
  // REALLY inefficient but is easy to read
  coordinate *origin = new coordinate();
  origin->setcoord(0.0, 0.0);
  // sort all on distance from origin
  for (int i = 0; i < col; i++) {
    if (nums[i]!=nullptr) {
      if (nums[i]->distance(origin) > nums[i + 1]->distance(origin)) {
        // i+1 is smaller
        swap(nums[i], nums[i + 1]);
      }
    }
  }
}

// in progress
// vector forms the rows of the two-dimensional euclidian plane
// coordinate ** represents a single line in the euclidian plane from left to
// right to look up or down, observe the respective row of nums and compare to
// MIN()
coordinate *closestpair(coordinate **nums) {
  // temp is used to measure distance from our current coordinate within nums
  // temp is FIXED and thus only other coordinates will be returned
  coordinate *temp;
#pragma omp parallel for
  for (int i = 8; i < 16; i++) {
    int k = 0;
    temp = &nums[i][k];
    // find away to implement minimum function
    if (temp->distance(&nums[i][k + 1]) < minim) {
      MIN(temp, temp->distance(&nums[i][k + 1]), MINSTACK);
    }

    k++;
  }
  for (int j = 8; j > 0; j--) {
    int k = 0;
    // find a way to implement minimum function
    if (temp->distance(&nums[j][k + 1]) < minim) {
      MIN(temp, temp->distance(&nums[j][k + 1]), MINSTACK);
    }
  }
  // temp used for nearest pair of points
  // return the pair as nums
  // sort nums
  // should now be sorted in terms of euclidian plane
  // split nums into left and right halves using algorithm
  return MINSTACK.top();
}
void printplane(coordinate **R) {
  coordinate *p = R[0];
  while (p != 0x0) {
    p->printcoords();
    p += sizeof(coordinate);
  }
  return;
}
int main(int argc, char **argv) {
  PlaneArithmetic *inst = new PlaneArithmetic();
  coordinate **array = inst->filein("in.txt");
  planesort(array, 16);
  //coordinate * p = closestpair(array);
  //cout << "CLOSEST:"
  //p->printcoords();
  // array set to array of points, now design sort below
  // fix below
  /*
    printplane(array);
  coordinate *ans = closestpair(array);
  */

  // array of numbers is now set, now for sorting and
  // good parse
}
