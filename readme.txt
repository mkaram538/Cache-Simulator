// File: readme.txt
// Author(s): Matthew Karam, Saul Diosdado
// Date: 04/23/2020
// Section: 508
// E-mail: sauldiosdado@tamu.edu
// Description:
// Explanation on compilation and execution of the program

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
