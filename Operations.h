// File: Opeations.h
// Author(s): Matthew Karam, Saul Diosdado
// Date: 04/23/2020
// E-mail: mkaram538@tamu.edu, sauldiosdado@tamu.edu
// Description:
// Used to declare and define helper functions that are used throughout the project.
// This project assignment was designed by Dr. David Kebo for the class CSCE 312: Computer Organization

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <map>
#include <string>
#include <iostream>
#include <math.h>
#include <bitset>
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

// Same as ^ but without 0x
string BaseTentoHexnoX(int number){
  string hex = "";
  hex += IntToString(number/16);
  hex += IntToString(number%16);
  return hex;
}

// Converts Hex "0x__" to binary
// TESTED
string HexToBinary(string number) {
  map<char, string> numbers = {
    {'0',"0000"}, {'1',"0001"}, {'2',"0010"}, {'3',"0011"}, {'4',"0100"},
    {'5',"0101"}, {'6',"0110"}, {'7',"0111"}, {'8',"1000"}, {'9',"1001"},
    {'A',"1010"}, {'B',"1011"}, {'C',"1100"}, {'D',"1101"},
    {'E',"1110"}, {'F',"1111"}
  };
  string binary = "";
  // Starts at index 2 to ignore the 0x
  for (int i = 2; i < number.size(); i++) {
    binary += numbers[number[i]];
  }
  // If the binary address is not 8 bits, add leading 0's.
  if (binary.size() != 8) {
    int numLead = 8 - binary.size();
    for (int i = 0; i < numLead; i++) {
      binary = "0" + binary;
    }
  }

  return binary;
}

// Converts decimal to 256-bit binary. Can be trimmed by BinaryTrim.
string DecimalToBinary(int dec) {
    return std::bitset<256>(dec).to_string();
}

// Trims a binary string to 'bits' number of bits.
string BinaryTrim(string binary, int bits) {
    string trimmedBinary;
    for (int i = binary.size() - bits; i < binary.size(); i++) {
        trimmedBinary += binary[i];
    }
    return trimmedBinary;
} 

// Converts a binary string to decimal.
// TESTED
int BinaryToInt(string binary) {
  int decimal = 0;
  for (int i = 0; i < binary.size(); i++) {
    if (binary[i] == '1') {
      decimal += pow(2, binary.size() - 1 - i);
    }
  }
  return decimal;
}

// Simple Hex to Integer for now
int HexToInt(string hex) {
  return BinaryToInt(HexToBinary(hex));
}

// Removes 0x from a hex string. E.g. 0xFF -> FF
// TESTED
string remove0x(string hex) {
  return hex.substr(2, hex.size() - 2);
}

#endif
