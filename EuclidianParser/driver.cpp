
#include "./code/EuclidianArithmetic.hpp"
#include <iterator>
std::stack<coordinate *> MINSTACK;
double minim = 0.0;
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

void planesort(coordinate **nums, int col) {
  // sort points in plane by distance from origin on a one-dimensional real line
  coordinate *origin = new coordinate();
  origin->setcoord(0.0, 0.0);
  // sort all on distance from origin
  for (int i = 0; i < col; i++) {
    coordinate *temp = nums[i];
    if (temp != nullptr) {
      for (int j = 0; j < col; j++) {
        if (nums[j] != temp &&
            nums[i]->distance(origin) > nums[j]->distance(origin) && i < j) {
          // i+1 is smaller
          swap(nums[i], nums[j]);
        }
      }
    }
  }
  delete origin;
  origin = nullptr;
}

// in progress
// vector forms the rows of the two-dimensional euclidian plane
// coordinate ** represents a single line in the euclidian plane from left to
// right to look up or down, observe the respective row of nums and compare to
// MIN()
coordinate *closestpair(coordinate **nums) {
  // take distance between all pairs using described algorithm splitting list
  // into left and right after origin sort furthest distance should be between
  // points on opposite end of splitted array
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
  char** t = argv;
  if(t+1!=nullptr){
  coordinate **array = inst->filein(t[1]);
  coordinate *p = closestpair(array);
  cout << minim << " is shortest distance" << endl;
  cout << "=END=" << endl;
  while (!MINSTACK.empty()) {
    MINSTACK.pop();
  }
  return 1;
  }
  else{
    cout << "INVALID FILENAME" <<endl;
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
