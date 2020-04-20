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
  int size = 0;
  vector<string> ram;

public:
  Memory(string filename){
    string line;
    ifstream ifs(filename);
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
