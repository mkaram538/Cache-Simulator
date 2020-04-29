#ifndef CACHE_H
#define CACHE_H

using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "replacement.h"

// Contains one block element, which is a vector of strings, each index
// holding a byte. The line also contains a valid bit and tag bit, and
// a variable declaring number of bytes which is equal to block_size
struct line
{
  int valid_bit = 0;
  int tag_bit;
  int num_bytes;
  int dirty_bit = 0;
  vector<string> block;

  line(vector<string> byte_list, int tag, int valid, int dirty)
  {
    block = byte_list;
    num_bytes = byte_list.size();
    tag_bit = tag;
    valid_bit = valid;
    dirty_bit = dirty;
  }

  // Returns reference to the string, so we can alter it easier
  string& operator[](int index){
    return block[index];
  }
};

// Contains a vector of lines, with num_lines many line objects.
struct sets
{
  int num_lines;
  vector<line> lines;
  replacement repl = replacement(0);

  sets(vector<line> line_list)
  {
    lines = line_list;
    num_lines = line_list.size();
    repl = replacement(num_lines);
  }

  // Returns true if there is an address line with matching tag and has valid bit 1.
  bool isPresentAndValid(int tag) {
    for (int i = 0; i < num_lines; i++) {
      if (lines[i].tag_bit == tag && lines[i].valid_bit == 1) {
        return true;
      }
    }
    return false;
  }

  // Returns the index of the line with matching tag. Makes sure that the valid bit
  // is also 1 in the case of duplicate tags in the same set.
  int getLineIndexOfTag(int tag) {
    for (int i = 0; i < num_lines; i++) {
      if (lines[i].tag_bit == tag && lines[i].valid_bit == 1) {
        return i;
      }
    }

    return -1;
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

  int t_bits, s_bits, b_bits;
  int num_sets;
  Memory& ram;

  // Stats
  int num_cache_hits = 0;
  int num_cache_misses = 0;

public:
  vector<sets> my_cache;
  // Add code to create set_size * num sets lines, with empty values and
  // valid bits of 0.
  Cache(Memory& myRAM, int cache, int block, int set, int repl, int hit, int miss) : ram(myRAM), cache_size(cache),
      block_size(block), set_size(set), repl_policy(repl), hit_policy(hit),
      miss_policy(miss)
  {
    num_sets = cache_size / (block_size * set_size);
    b_bits = (int) log2(block_size);
    s_bits = (int) log2(num_sets);
    t_bits = 8 - s_bits - b_bits; // Address is always 8 bits for this assignment

    // The following initializes a cold cache, where each line has no data and valid bit = 0
    vector<string> emptyBlock(block_size); // Empty vector with size = block_size
    for (int i = 0; i < block_size; i++) {
      emptyBlock[i] = ("00");
    }
    vector<line> coldLines;
    line coldLine(emptyBlock, 0, 0, 0); // Represents an empty cache line
    for (int i = 0; i < set_size; i++) {
      coldLines.push_back(coldLine);
    }
    sets coldSet(coldLines);
    for (int i = 0; i < num_sets; i++) {
      my_cache.push_back(coldSet);
    }
  }

  void read(string address) {
    //TESTED: for read hit and read miss with LRU and random, haven't
    // tested or added the option for LFU but have written it.
    // Convert address from hex to binary
    string binaryAddress = HexToBinary(address);

    string tagBinary = binaryAddress.substr(0, t_bits);
    string indexBinary = binaryAddress.substr(t_bits, s_bits);
    string offsetBinary = binaryAddress.substr(t_bits + s_bits, b_bits);

    int tag = BinaryToInt(tagBinary);
    int set = BinaryToInt(indexBinary);
    int block = BinaryToInt(offsetBinary);

    // Determines if hit or miss.
    if (my_cache[set].isPresentAndValid(tag)) {
      // Hit, both the tag matched and the valid bit was 1.
      num_cache_hits++;
      int lineNum = my_cache[set].getLineIndexOfTag(tag);
      string readData = my_cache[set][lineNum][block];
      my_cache[set].repl.access(lineNum);

      cout << "set:" << set << endl;
      // Assuming tag is in base ten, otherwise change to BaseTentoHex(tag)
      cout << "tag:" << tag << endl;
      cout << "hit:yes" << endl;
      cout << "eviction_line:-1" << endl;
      cout << "ram_address:-1" << endl;
      cout << "data:0x" << readData << endl;
    } else {
      // Miss
      num_cache_misses++;
      vector<string> blockFromRam = ram.getBlock(HexToInt(address) / block_size, block_size);
      int lineNum; // Index of the line to replace, determined by the replacement policies
      // TODO: Replacement Policies
      bool empty_line = false;
      for (int i = 0; i < set_size; i++){
        if (my_cache[set][i].valid_bit == 0){
          lineNum = i;
          empty_line = true;
          break;
        }
      }
      if (empty_line == false){
        if (repl_policy == 1) { // random_replcaement
          srand(time(NULL));
          lineNum = rand() % set_size;
        } else if (repl_policy == 2) { // least_recently_used
          if (set_size == 1){
            lineNum = 0;
          } else {
            lineNum = my_cache[set].repl.LRU();
            my_cache[set].repl.clear(lineNum);
            my_cache[set].repl.access(lineNum);
          }
        } else if (repl_policy == 3) {
          if (set_size == 1){
            lineNum = 0;
          } else {
            lineNum = my_cache[set].repl.LFU();
            my_cache[set].repl.clear(lineNum);
            my_cache[set].repl.access(lineNum);
          }
        }
      }
      // Write the block retrieved from RAM to the line determined by the replacement policy
      for (int i = 0; i < block_size; i++) {
        my_cache[set][lineNum][i] = blockFromRam[i];
      }
      my_cache[set][lineNum].valid_bit = 1;
      my_cache[set][lineNum].dirty_bit = 0;
      my_cache[set][lineNum].tag_bit = tag;
      // The data that is read from the cache line to be returned.
      string readData = my_cache[set][lineNum][block];

      cout << "set:" << set << endl;
      // Assuming tag is in base ten, otherwise change to BaseTentoHex(tag)
      cout << "tag:" << tag << endl;
      cout << "hit:no" << endl;
      cout << "eviction_line:" << lineNum << endl;
      cout << "ram_address:" << address << endl;
      cout << "data:0x" << readData << endl;
    }
  }

  //TESTED write miss and hit for 1/1/1 and 1/2/2, will go into 2/?/?
  //later for further testing
  void write(string address, string data) {
    // Convert address from hex to binary
    string binaryAddress = HexToBinary(address);
    string tagBinary = binaryAddress.substr(0, t_bits);
    string indexBinary = binaryAddress.substr(t_bits, s_bits);
    string offsetBinary = binaryAddress.substr(t_bits + s_bits, b_bits);

    int tag = BinaryToInt(tagBinary);
    int set = BinaryToInt(indexBinary);
    int block = BinaryToInt(offsetBinary);

    // Determines if hit or miss.
    if (my_cache[set].isPresentAndValid(tag)) {
      // Hit, both the tag matched and the valid bit was 1.
      num_cache_hits++;
      int lineNum = my_cache[set].getLineIndexOfTag(tag);
      my_cache[set].repl.access(lineNum);
      bool dirtyBitChange = false;

      if (hit_policy == 1) { // write-through
        // Update cache
        my_cache[set][lineNum][block] = remove0x(data); // Updates specific byte in cache
        my_cache[set][lineNum].valid_bit = 1;
        // Update RAM block with entire block from cache
        ram.writeBlock(HexToInt(address) / block_size, my_cache[set][lineNum].block);
      } else if (hit_policy == 2) { // write-back
        // Update cache
        my_cache[set][lineNum][block] = remove0x(data);
        my_cache[set][lineNum].valid_bit = 1;
        my_cache[set][lineNum].dirty_bit = 1;
        dirtyBitChange = true;
      }

      cout << "set:" << set << endl;
      // Assuming tag is in base ten, otherwise change to BaseTentoHex(tag)
      cout << "tag:" << tag << endl;
      cout << "write_hit:yes" << endl;
      cout << "eviction_line:-1" << endl;
      cout << "ram_address:-1" << endl;
      cout << "data:" << data << endl;
      cout << "dirty_bit:" << dirtyBitChange << endl;
    } else {
      // Miss, either the tag was not present or the valid bit was 0.
      int lineNum;
      bool dirtyBitChange = false;
      num_cache_misses++;
      if (miss_policy == 1) { // write-allocate
        vector<string> blockFromRam = ram.getBlock(HexToInt(address) / block_size, block_size);
        bool empty_line = false;
        for (int i = 0; i < set_size; i++){
          if (my_cache[set][i].valid_bit == 0){
            lineNum = i;
            empty_line = true;
            break;
          }
        }
        if (empty_line == false){
          if (repl_policy == 1) { // random_replcaement
            srand(time(NULL));
            lineNum = rand() % set_size;
          } else if (repl_policy == 2) { // least_recently_used
            if (set_size == 1){
              lineNum = 0;
            } else {
              lineNum = my_cache[set].repl.LRU();
            }
          } else if (repl_policy == 3) {
            if (set_size == 1){
              lineNum = 0;
            } else {
              lineNum = my_cache[set].repl.LFU();
            }
          }
        }
        // Takes the block from RAM and write is to cache
        for (int i = 0; i < block_size; i++) {
          my_cache[set][lineNum][i] = blockFromRam[i];
        }
        my_cache[set][lineNum].valid_bit = 1;
        my_cache[set][lineNum].dirty_bit = 0;
        my_cache[set][lineNum].tag_bit = tag;
        my_cache[set].repl.clear(lineNum);
        my_cache[set].repl.access(lineNum);

        if (hit_policy == 1) { // write-through
          // Update cache
          my_cache[set][lineNum][block] = remove0x(data); // Updates specific byte in cache
          my_cache[set][lineNum].valid_bit = 1;
          // Update RAM block with entire block from cache
          ram.writeBlock(HexToInt(address) / block_size, my_cache[set][lineNum].block);
        } else if (hit_policy == 2) { // write-back
          // Update cache
          my_cache[set][lineNum][block] = remove0x(data);
          my_cache[set][lineNum].valid_bit = 1;
          my_cache[set][lineNum].dirty_bit = 1;
          dirtyBitChange = true;
        }

      } else if (miss_policy == 2) { // no-write-allocate
        ram.writeByte(HexToInt(address), remove0x(data)); // Update RAM
        lineNum = -1; //I don't know what this value is supposed to be,
        // because we are not evicting a line, but it's not a write-hit
      }
      cout << "set:" << set << endl;
      // Assuming tag is in base ten, otherwise change to BaseTentoHex(tag)
      cout << "tag:" << tag << endl;
      cout << "write_hit:no" << endl;
      cout << "eviction_line:" << lineNum << endl;
      cout << "ram_address:" << address << endl;
      cout << "data:" << data << endl;
      cout << "dirty_bit:" << dirtyBitChange << endl;

    }
  }
  //TESTED
  void flush() {
    my_cache.clear();
    // The following initializes a cold cache, where each line has no data and valid bit = 0
    vector<string> emptyBlock(block_size); // Empty vector with size = block_size
    for (int i = 0; i < block_size; i++) {
      emptyBlock[i] = ("00");
    }
    vector<line> coldLines;
    line coldLine(emptyBlock, 0, 0, 0); // Represents an empty cache line
    for (int i = 0; i < set_size; i++) {
      coldLines.push_back(coldLine);
    }
    sets coldSet(coldLines);
    for (int i = 0; i < num_sets; i++) {
      my_cache.push_back(coldSet);
    }
  }

  // TESTED
  void view() {
    cout << "cache_size:" << cache_size << endl;
    cout << "data_block_size:" << block_size << endl;
    cout << "associativity:" << set_size << endl;
    if (repl_policy == 1) {
      cout << "replacement_policy:random_replacement" << endl;
    } else if (repl_policy == 2) {
      cout << "replacement_policy:least_recently_used" << endl;
    } else if (repl_policy == 3) {
      cout << "replacement_policy:least_frequently_used" << endl;
    }
    if (hit_policy == 1) {
      cout << "write_hit_policy:write_through" << endl;
    } else if (hit_policy == 2) {
      cout << "write_hit_policy:write_back" << endl;
    }
    if (miss_policy == 1) {
      cout << "write_miss_policy:write_allocate" << endl;
    } else if (miss_policy == 2) {
      cout << "write_miss_policy:no_write_allocate" << endl;
    }
    cout << "number_of_cache_hits:" << num_cache_hits << endl;
    cout << "number_of_cache_misses:" << num_cache_misses << endl;
    cout << "cache_content:" << endl;
    for (int i = 0; i < num_sets; i++) {
      for (int j = 0; j < set_size; j++) {
        line thisLine = my_cache[i][j];
        cout << thisLine.valid_bit << " " << thisLine.dirty_bit << " " << BaseTentoHexnoX(thisLine.tag_bit) << " ";
        for (int k = 0; k < block_size; k++) {
          cout << thisLine[k].substr(0,2) << " ";
        }
        cout << endl;
      }
    }
  }

  // TESTED for cold cache (prints all 0's).
  void dump() {
    ofstream fileWriter("cache.txt");
    for (int i = 0; i < num_sets-1; i++) {
      for (int j = 0; j < set_size; j++) {
        for (int k = 0; k < block_size; k++) {
          fileWriter << my_cache[i][j][k] << " ";
        }
        fileWriter << endl;
      }
    }
    for (int j = 0; j < set_size-1; j++) {
      for (int k = 0; k < block_size; k++) {
        fileWriter << my_cache[num_sets-1][j][k] << " ";
      }
      fileWriter << endl;
    }
    for (int k = 0; k < block_size; k++) {
      fileWriter << my_cache[num_sets-1][set_size-1][k] << " ";
    }
    fileWriter.close();
  }
};


#endif
