#include <iostream>
#include <string>

#include "Memory.h"
#include "Operations.h"
#include "Cache.h"

using namespace std;

// I'm thinking this function will print out the menu and call the function
// that the user is trying to run. So for instance, menu() will output the menu
// then the user will type in cache-read 0x18 and menu() will call
// cache.read(00011000) or cache.read(24) depending on how we decide to deal
// with hex numbers
// if user inputs quit, return 0 and that'll be the loop breaking condition

int menu(Memory ram, Cache cache){ //Should also take in a cache object, when written
  cout << "*** Cache simulator menu ***" << endl;
  cout << "type one command: " << endl;
  cout << "1. cache-read" << endl;
  cout << "2. cache-write" << endl;
  cout << "3. cache-flash" << endl;
  cout << "4. cache-view" << endl;
  cout << "5. memory-view" <<  endl;
  cout << "6. cache-dump" << endl;
  cout << "7. memory-dump" << endl;
  cout << "8. quit" << endl;
  cout << "****************************" << endl;

  string choice;
  cin >> choice;

  if (choice == "cache-read")
  {
    string address;
    cin >> address;
    cache.read(address);
    return 1;
  } else if (choice == "cache-write")
  {
    string address, value;
    cin >> address >> value;
    cache.write(address, value);
    return 1;
  } else if (choice == "cache-flush")
  {
    cache.flush();
    return 1;
  } else if (choice == "cache-view")
  {
    cache.view();
    return 1;
  } else if (choice == "memory-view")
  {
    //TESTED
    ram.view();
    return 1;
  } else if (choice == "cache-dump")
  {
    cache.dump();
    return 1;
  } else if (choice == "memory-dump")
  {
    //TESTED
    ram.dump();
    return 1;
  } else if (choice == "quit")
  {
    // This will be a condtional that ends the loop of calling menu().
    return 0;
  }

  return 0;
}

int main(){
  //Testing the Memory Creation
  //TESTED
  cout << "*** Welcome to the cache simulator ***" << endl;
  string filename;
  cout << "Initialize the RAM: " << endl;
  cout << "init-ram 0x00 0xff" << endl;
  Memory MyRam = Memory("input.txt");
  cout << "ram succesfully initialized!" << endl;

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
  cout << "cache succesfully configured!" << endl;

  Cache cache(MyRam, cache_size, block_size, associativity, repl_policy, hit_policy, miss_policy);

  int loop_conditional = 1;
  while (loop_conditional == 1){
    loop_conditional = menu(MyRam, cache);
  };


  return 0;
}
