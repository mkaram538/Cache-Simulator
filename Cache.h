#ifndef CACHE_H
#define CACHE_H

using namespace std;
#include <iostream>
#include <vector>
#include <string>

struct block
{
  int num_bytes;
  vector<string> bytes;

  block(vector<string> byte_list)
  {
    bytes = byte_list;
    num_bytes = byte_list.size();
  }
};

struct line
{
  int num_blocks;
  int valid_bit;
  int tag_bit;
  vector<block> blocks;

  line(vector<block> block_list)
  {
    blocks = block_list;
    num_blocks = block_list.size();
  }
};

struct set
{
  int num_lines;
  vector<line> lines;

  set(vector<line> line_list)
  {
    lines = line_list;
    num_lines = line_list.size();
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
  Cache(int cache, int block, int set, int repl, int hit, int miss) : cache_size(cache),
      block_size(block), set_size(set), repl_policy(repl), hit_policy(hit),
      miss_policy(miss)
  {

  }
};


#endif
