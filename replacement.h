// File: replacement.h
// Author(s): Matthew Karam, Saul Diosdado
// Date: 04/23/2020
// E-mail: mkaram538@tamu.edu, sauldiosdado@tamu.edu
// Description:
// Implements both LFU and LRU replacement policies.
// This project assignment was designed by Dr. David Kebo for the class CSCE 312: Computer Organization

#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "Cache.h"
#include "Memory.h"
#include "Operations.h"
#include <map>
#include <iostream>
#include <string>

using namespace std;

struct Node
{
  int index;
  int uses;
  Node* next = nullptr;
  //Node* prev = nullptr;

  Node (int line_index){
    index = line_index;
    uses = 0;
  }
};

class replacement
{
private:
  Node* head = nullptr;
  Node* tail = nullptr;

public:
  replacement (int num_lines){
    for (int i = 0; i < num_lines; i++){
      insert(i);
    }
  }

  void insert(int index){
    Node* current = new Node(index);
    if (!head){
      head = current;
      tail = current;
    }
    else if (!head->next){
      tail = current;
      head->next = tail;
      //tail->prev = head;
    } else {
      //current->prev = tail;
      tail->next = current;
      tail = current;
    }
  }

  void access(int search){
    Node* current = head;
    if (head == tail){//happens when size == 1
      head->uses++;
      return;
    } else if (head->index == search){
      head = current->next;
      current->next = nullptr;
      //current->prev = tail;
      tail->next = current;
      tail = current;
      current->uses++;
      return;
    } else if (tail->index == search){
      tail->uses++;
      return;
    }
    current = head;
    Node* node = current;
    while (current->next->index != search){
      current = current->next;
    }
    //current->next->prev = current->prev;
    //current->prev->next = current->next;
    node = current->next;
    current->next = node->next;
    //current->prev = tail;
    tail->next = node;
    node->next = nullptr;
    tail = node;
    tail->uses++;
  }

  // Used when a line is evicted
  void clear(int search){
    Node* current = head;
    if (head->index == search){
      current->uses = 0;
      return;
    } else if (tail->index == search){
      tail->uses = 0;
      return;
    }
    while (current->index != search){
      current = current->next;
    }
    current->uses = 0;
  }

  // TESTED, the way the linked_list is set up, the only way that there
  // would be equal values is if it was in the beginning, and those lines
  // are already in order based on index
  int LRU() {
    return head->index;
  }

  // Finds the line with the smallest number of uses, favoring the line with
  // the lower index.
  int LFU() {
    Node* current = head;
    int min_occur = current->uses;
    int min_index = current->index;
    int index = 0;
    while (current){
      if (current->uses < min_occur){
        min_index = current->index;
        min_occur = current->uses;
      } else if (current->uses == min_occur && index < min_index){
        min_index = current->index;
      }
      current = current->next;
      index++;
    }
    return min_index;
  }

  // Used in testing
  void print(){
    Node* current = head;
    while (current){
      cout << "Index: " << current->index << " Uses: " << current->uses << endl;
      current = current->next;
    }
  }
};

#endif
