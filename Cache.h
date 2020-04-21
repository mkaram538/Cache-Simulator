#ifndef CACHE_H
#define CACHE_H

using namespace std;
#include <iostream>
#include <vector>
#include <string>

// Contains one block element, which is a vector of strings, each index
// holding a byte. The line also contains a valid bit and tag bit, and
// a variable declaring number of bytes which is equal to block_size
struct line
{
  int valid_bit=0;
  int tag_bit;
  int num_bytes;
  vector<string> block;

  line(vector<string> byte_list, int tag, int valid)
  {
    block = byte_list;
    num_bytes = byte_list.size();
    tag_bit = tag;
    valid_bit = valid;
  }

  // Returns reference to the string, so we can alter it easier
  string& operator[](int index){
    return block[index];
  }
};

// Contains a vector of lines, with num_lines many line objects.
struct set
{
  int num_lines;
  vector<line> lines;

  set(vector<line> line_list)
  {
    lines = line_list;
    num_lines = line_list.size();
  }

  // Returns reference to line at the given index, so we can alter it easier
  line& operator[](int index){
    return lines[index];
  }
};

class Cache{
private:
  int cache_size;
  int block_size;
  int set_size;
  int repl_policy;
  int hit_policy;
  int miss_policy;
  vector<set> sets;
public:

  // Add code to create set_size * num sets lines, with empty values and
  // valid bits of 0.
  Cache(int cache, int block, int set, int repl, int hit, int miss) : cache_size(cache),
      block_size(block), set_size(set), repl_policy(repl), hit_policy(hit),
      miss_policy(miss)
  {

  }
};


#endif
