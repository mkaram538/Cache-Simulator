// File: Memory.h
// Author(s): Matthew Karam, Saul Diosdado
// Date: 04/23/2020
// E-mail: mkaram538@tamu.edu, sauldiosdado@tamu.edu
// Description:
// Holds the entire RAM space.
// This project assignment was designed by Dr. David Kebo for the class CSCE 312: Computer Organization

#ifndef MEMORY_H
#define MEMORY_H

using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Operations.h"

class Memory
{
private:
  //The RAM is stored in a vector of strings, I'm thinking we just convert
  //from string to int later.
  int size = 0;
  vector<string> ram;

public:
  Memory(string filename){
    string line;
    ifstream ifs(filename);
    //Takes in the name of the file as it's input and reads through it
    //line by line adding the byte in string form to the vector
    //TESTED
    for (int i = 0; i < 256; i++){
      string byte;
      ifs >> byte;
      ram.push_back(byte);
      size++;
    }
  };

  // Prints out the memory object's information
  // and the contents of the ram vector in rows of 8 bytes
  // TESTED

  void view(){
    string line;
    cout << "memory_size:" << size << endl;
    cout << "memory_content:" << endl;
    cout << "Address:Data" << endl;

    for (int i = 0; i < 256/8;i++){
      line = BaseTentoHex(i*8) + ":";
      for (int p = 0; p < 8; p++){
        line = line + ram[i*8 + p].substr(0,2) + " ";
      }
      cout << line << endl;
    }
    return;
  }

  // Opens ram.txt and prints each value in ram on a seperate line.
  void dump(){
    ofstream ofs;
    ofs.open("ram.txt");

    for (int i = 0; i < 255; i++){
      ofs << ram[i] << "\n";
    }
    // split apart so only 256 lines are written into ram.txt
    ofs << ram[255];

    ofs.close();
  }

  void print(){
    for (int i = 0; i < 256;i++){
      cout << ram[i] << endl;
    }
  };

  // Writes the block to RAM
  void writeBlock(int block_num, const vector<string> block) {
    //
    int offset = block_num * block.size();
    for (int i = 0; i < block.size(); i++) {
      ram[i + offset] = block[i];
    }
  }

  // Overrite a single byte in RAM, used for write-miss no allocate policy
  // byte_index is an integer between 0 - (block_size - 1)
  void writeByte(int byte_index, string byte) {
    ram[byte_index] = byte;
  }

  // Gets block from RAM given the block number and the size of the block
  vector<string> getBlock(int block_num, int block_size) {
    vector<string> block(block_size);
    int offset = block_num * block.size();
    for (int i = 0; i < block_size; i++) {
      block[i] = ram[i + offset];
    }

    return block;
  }


};

#endif
