#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <map>
#include <string>
#include <iostream>
#include "Memory.h"

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
};

string IntToString(int number){
  map<int, string> letters = {
    {0,"0"}, {1,"1"}, {2,"2"}, {3,"3"}, {4,"4"},
    {5,"5"}, {6,"6"}, {7,"7"}, {8,"8"}, {9,"9"},
    {10,"A"}, {11,"B"}, {12,"C"}, {13,"D"},
    {14,"E"}, {15,"F"}
  };
  return letters[number];
}

// Using this to make it easier to label ram lines in ram.view(), intial
// intention is to only use this for 0-255, can expand if useful in other places
string BaseTentoHex(int number){
  string hex = "0x";
  hex += IntToString(number/16);
  hex += IntToString(number%16);
  return hex;
}

#endif
