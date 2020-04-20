#include <iostream>
#include <string>

#include "Memory.h"
#include "Operations.h"

using namespace std;

int main(){
  //Testing the Memory Creation
  //TESTED
  cout << "*** Welcome to the cache simulator ***" << endl;
  string filename;
  cout << "Initialize the RAM: ";
  cin >> filename;
  cout << "init-ram 0x00 0xff" << endl;
  cout << "ram succesfully initialized!" << endl;

  Memory MyRam = Memory(filename);

  //Cache configuring
  //variables
  int cache_size;
  int block_size;
  int associativity;
  int repl_policy;
  int hit_policy;
  int miss_policy;

  //Variable gathering, in the proper form
  cout << "configure the cache:" << endl;
  cout << "cache size: ";
  cin >> cache_size;
  cout << "data block size: ";
  cin >> block_size;
  cout << "associativity: ";
  cin >> associativity;
  cout << "replacement policy: ";
  cin >> repl_policy;
  cout << "write hit policy: ";
  cin >> hit_policy;
  cout << "write miss policy: ";
  cin >> miss_policy;
  cout << "cache succesfully configured!";



  return 0;
}
