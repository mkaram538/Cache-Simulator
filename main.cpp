#include <iostream>
#include <string>

#include "Memory.h"

using namespace std;

int main(){
  string filename;
  cout << "Initialize the RAM: " << endl;
  cin >> filename;

  Memory MyRam = Memory(filename);

  cout << "Change Testing" << endl;

  return 0;
}
