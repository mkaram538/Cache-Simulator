#ifndef MEMORY_H
#define MEMORY_H

using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

  void print(){
    for (int i = 0; i < 256;i++){
      cout << ram[i] << endl;
    }
  }


};

#endif
