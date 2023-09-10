
#include "./code/EuclidianArithmetic.hpp"

double minim = 0.0;
void swap(coordinate **a, coordinate **b) {
  coordinate *temp = *b;
  *b = *a;
  *a = temp;
}
void twoDimBubbleSort(vector<coordinate **> nums, int row, int col) {
  // REALLY inefficient but is easy to read
  for (int i = 0; i < (row * col); ++i) {
    for (int j = 0; j < (row * col) - 1; ++j) {
      int cr = j / col;       // current row
      int cc = j % col;       // current column
      int nr = (j + 1) / col; // next item row
      int nc = (j + 1) % col; // next item column

      if (nums[cr][cc]->x0() >= nums[nr][nc]->x0() &&
          nums[cr][cc]->x1() > nums[nr][nc]->x1()) {
        swap(&nums[cr][cc],
             &nums[nr][nc]); // any way you want to swap variables
      }
    }
  }
}
std::stack<coordinate *> MINSTACK;
// in progress
void MIN(coordinate *coord, double distance, std::stack<coordinate *> stck) {
  if (distance < minim) {
    stck.push(coord);
  }
}
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
      MIN(&nums[i][k + 1], temp->distance(&nums[i][k + 1]), MINSTACK);
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
int main(int argc, char **argv) {
  PlaneArithmetic *inst = new PlaneArithmetic();
  coordinate **array = inst->filein("in.txt");
  // array of numbers is now set, now for sorting and
  // good parse
}
