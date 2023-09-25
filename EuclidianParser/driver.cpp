#include "./code/NumParse.hpp"
std::stack<coordinate *> comp;
// TESTS
// 1 1.40118 good
// 2 1.51069 wrong
// 3 2.702 wrong
// 4 1.25196 wrong
// 5 3.15855 wrong
// 6 0.651304 wrong
// 7 0.82 wrong
// 8 0.41 good
// 9 0.07 good
// 10 0 good
// g++ driver.cpp && ./a.out 1.txt
void swap(coordinate *a, coordinate *b) {
  coordinate temp = *b;
  *b = *a;
  *a = temp;
}

vector<vector<coordinate *> *> copyVec(vector<coordinate *> src) {
  vector<vector<coordinate *> *> ans;
  __wrap_iter<coordinate **> mid = src.begin() + (src.size() / 2);
  vector<coordinate *> *L = new vector<coordinate *>(src.begin(), mid);
  vector<coordinate *> *R = new vector<coordinate *>(mid, src.end());
  ans.push_back(L);
  ans.push_back(R);
  return ans;
}

void minimum_distance_split(vector<coordinate *> nums1,
                            vector<coordinate *> nums2, long double *ans1,
                            long double *ans2) {
  // take distance between all pairs using described algorithm splitting list
  // into left and right after origin sort furthest distance should be between
  // points on opposite end of splitted array
  long double minimum = std::numeric_limits<long double>::max();
  long double ans = std::numeric_limits<long double>::max();
  coordinate *p = 0x0;
  coordinate *R = 0x0;
  coordinate *L = 0x0;
  coordinate *p2 = 0x0;
  coordinate *R2 = 0x0;
  coordinate *L2 = 0x0;
// split the array along our line at p, and then break array into left and
// right sets to recursively solve
// should segfault if one array is not equal to other
#pragma omp parallel for
  for (unsigned x = 1; x + 1 < nums1.size(); x ++) {
    p = nums1[x];
    R = nums1[x + 1];
    L = nums1[x - 1];
    p2 = nums2[x];
    R2 = nums2[x + 1];
    L2 = nums2[x - 1];
    p->distance(R) < minimum ? minimum = p->distance(R) : minimum = minimum;
    p->distance(L) < minimum ? minimum = p->distance(L) : minimum = minimum;
    p2->distance(R2) < ans ? ans = p2->distance(R2) : ans = ans;
    p2->distance(L2) < ans ? ans = p2->distance(L2) : ans = ans;
  }
  *ans1 = minimum;
  *ans2 = ans;

  //  nums1.size() - nums2.size() == 0 ? run : return;
}

vector<coordinate *> generate_candidate_strip(vector<coordinate *> nums,
                                              long double *_distance) {
  // take distance between all pairs using described algorithm splitting list
  // into left and right after origin sort furthest distance should be between
  // points on opposite end of splitted array
  // R and L wont always be the same size, how to ensure they are?
  unsigned mid = nums.size() / 2;
   coordinate *const p = nums[mid];
  vector<vector<coordinate *> *> split = copyVec(nums);
  vector<coordinate *> *R = split[0];
  vector<coordinate *> *L = split[1];
  comp.push(p);
  vector<coordinate *>::iterator r_itr = R->begin();
  vector<coordinate *>::iterator l_itr = L->begin();
  long double minL, minR;
  minimum_distance_split(*L, *R, &minL, &minR);
  long double distance = std::min(minL, minR);
  *_distance = distance;
  // split the array along our line at p, and then break array into left and
  // right sets to recursively solve might not work for all cases because we
  // have converted 2d coordinates to 1d. will need to fix this
  // save p for later comparison
  vector<coordinate *> candidate = vector<coordinate *>();
// array of iterators which contain our points of interest
#pragma omp parallel for
  for (unsigned x = 0; x < mid; x++) {
    long double leftdist = p->distance(*l_itr);
    if (leftdist <= distance) {
      candidate.push_back(*l_itr);
    }
    long double rightdist = p->distance(*r_itr);
    if (rightdist <= distance) {
      candidate.push_back(*r_itr);
    }
    r_itr++;
    l_itr++;
  }
  return candidate;
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

class Comparey {
public:
  // a is less than b operator, used for sort in R^2
  bool operator()(coordinate *a, coordinate *b) {
    return a->x1() < b->x1() ? a->x1() : b->x1();
  }
};

long double smallestdist(vector<coordinate *> strip, long double best) {
  for (int i = 0; i < strip.size(); ++i) {
    unsigned counter = 0;
    for (int j = ++i; j < strip.size() &&
                      (strip[j]->x1() - strip[i]->x1()) < best && counter < 8;
         ++j) {
      if (strip[i]->distance(strip[j]) < best)
        best = strip[i]->distance(strip[j]);
      counter++;
    }
  }
  // coordinate * p = strip[strip.size()/2]; ??
  // pick all points one by one, and check that their distance between points
  // is lower than minimum distance d
  return best;
}

int main(int argc, char **argv) {
  PlaneArithmetic *inst = new PlaneArithmetic();
  if (argv[1] != nullptr) {
    vector<coordinate *> *array = inst->filein(argv[1]);
    if (array->empty()) {
      cout << "EMPTY, NO NUMBERS FOUND IN FILE" << endl;
      return -1;
    } else {
      // split array into two equal subsets;
      std::sort(array->begin(), array->end(), Compare());
      printplane(*array);
      long double dist;
      vector<coordinate *> strip = generate_candidate_strip(*array, &dist);
      std::sort(strip.begin(), strip.end(), Comparey());
      cout << smallestdist(strip, dist) << " is shortest distance" << endl;
      cout << "=END=" << endl;
      return 1;
    }
  } else {
    cout << "INVALID FILENAME" << endl;
    return -1;
  }
}
