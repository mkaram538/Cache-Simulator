// File: readme.txt
// Author(s): Matthew Karam, Saul Diosdado
// Date: 04/23/2020
// E-mail: sauldiosdado@tamu.edu
// Description:
// Explanation on compilation and execution of the program
// This project assignment was designed by Dr. David Kebo for the class CSCE 312: Computer Organization

Introduction
In this project, we created a cache-memory simulator. This project highlighted the organization of both cache and memory, as well as the ability to configure and manipulate the
data in both using read and write methods. The program allowed the user to understand the different effects associated with the different hit, miss, and replacement policies as
well. This report will go over the organization associated with both the simulated cache and memory, as well as the ways in which the various methods associated with these data
structures work. 

Design and Implementation
Memory: We used a vector of strings of size 256 to represent memory, this vector was used to store and index the data read from input.txt. Both memory-view and memory-dump were
done by iterating through the vector, and printing to screen or writing to ram.txt respectively.

Cache: We used a 3-D vector to represent cache. The outermost being a vector of sets, each set containing a vector of lines, each line containing a vector of strings, used to
store the bytes read in from memory, as well as the valid, dirty, and tag bits. We created as many functions as possible to not only increase the flexibility of the program but
also increase code readability and allow for easier debugging. For this, we created a file containing only helper functions, such as conversions from and to hex, decimal, and
string. Cache-read first converts the address to binary using one of the helper functions, then splits each of the bits to the corresponding tag, set, and block variables. The
function then takes on a flow-chart style, where if statements determine if a hit or miss occurred, followed by more if statements to determine what to do based on the different
replacement policies. Cache-write is the same for breaking down the address and goes more in-depth where if statements determine what is read from RAM, written to RAM, etc.
Cache-flush first writes all lines that have the dirty bit asserted to RAM, then proceeds to clear the outermost vector of the 3-D vector, which has the same effect of clearing
the entire cache. The cache is then initialized to a cold cache, where all lines are 0 for the valid bit, dirty bit, tag bits, and the entire block. Cache-view simply prints out
all of the information from the cache, including the blocks. The dump function creates a new file called “cache.txt” and fills it with all blocks of the cache memory, one block
per line. It does so by again using a triple for-loop.

Replacement Policy: The line to evict for random replacement was chosen, by choosing a random number between 0 and the number of lines per set. LRU and LFU were implemented by
first creating a separate linked list for each set in the cache. Each node in the list represents a line in the set and keeps a counter to determine the number of accesses of
that line. Each time a node was accessed, that node was moved to the tail of the list, and its counter was incremented. Each time a line was evicted, that line’s counter was
reset to 0 and then accessed. LRU returns the head because that is the line accessed least recently, and LFU returns the line with the smallest access count, with a bias towards
nodes with a smaller index.

Compile: g++ cachesimulator.cpp -o cachesimulator.out
Execute: ./cachesimulator.out "filename"

User inputs:
1. cache-size (integer)
2. block-size (integer)
3. associativity (integer)
4. replacement policy (1: Random, 2: LRU, 3: LFU)
5. write-hit policy (1: write-through, 2: write-back)
6. write-miss policy (1: write-allocate, 2: no write-allocate)
7...(until quit) menu option: (cache-read 0x(address),
  cache-write 0x(address) 0x(value), cache-flush, cache-view, memory-view,
  cache-dump, memory-dump, quit)

Ex:
g++ cachesimulator.cpp -o out
./out input.txt
64
4
4
3
1
1
cache-read 0xE2
cache-view
quit
