#include "../Algorithms/algo.hpp"
#include "../Algorithms/bits.hpp"
#include <iostream>

using namespace std;



int main(int argc, char ** argv){

if(strcmp(argv[1], "string")==0){
  cout << "Enter your input below." << endl;
  string in;
  cin>> in;
  Solution *algo= new Solution();
  algo->minimizedStringLength(in);
  cout << "AFTER EXCAVATION:" <<endl;
  cout << in << endl;
}
else {
cout << "No input given." <<endl;
}


}