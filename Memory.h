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
      getline(ifs,line);
      ram.push_back(line);
      size++;
    }
  };

  string getValue(int index){
    return this->ram[index];
  }
  //Having some weird print bugs, will fix
  /*
  void view(){
    string line;
    cout << "memory_size:" << size << endl;
    cout << "memory_content:" << endl;
    cout << "Address:Data" << endl;
    for (int i = 0; i < 256/8;i++){
      line =  BaseTentoHex(i*8) + ":";
      for (int p = 0; p < 8; p++){
        line = line + getValue(i*8 + p) + " ";
      }
      cout << line << endl;
    }
    return;
  };
  */
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




};

#endif
