#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

//Just something we might use to help convert from a hex string
//to base 10, will probably use this in a base converter given a string.
//TESTED
int StringToInt(string number){
  map<string, int> numbers = {
    {"0",0}, {"1",1}, {"2",2}, {"3",3}, {"4",4},
    {"5",5}, {"6",6}, {"7",7}, {"8",8}, {"9",9},
    {"A",10}, {"B",11}, {"C",12}, {"D",13},
    {"E",14}, {"F",15}
  };
  return numbers[number];
}

#endif
