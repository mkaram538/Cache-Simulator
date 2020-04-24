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
  Node* prev = nullptr;

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
      tail->prev = head;
    } else {
      current->prev = tail;
      tail->next = current;
      tail = current;
    }
  }

  void access(int search){
    Node* current = head;
    if (head->index == search){
      head = current->next;
      current->next = nullptr;
      current->prev = tail;
      tail->next = current;
      tail = current;
      current->uses++;
      return;
    } else if (tail->index == search){
      current->uses++;
      return;
    }
    while (current->index != search){
      current = current->next;
    }
    current->uses++;
    current->next->prev = current->prev;
    current->prev->next = current->next;

    current->prev = tail;
    current->next = nullptr;
    tail->next = current;
    tail = current;
  }

  //TESTED
  int LRU() {
    return head->index;
  }
};

#endif
