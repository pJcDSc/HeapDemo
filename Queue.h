/* 
Author: Peter Jin
Date: 2/1/20
Heap Demo Queue header
*/

#include <iostream>
#include "Node.h"

#ifndef QUEUE_H
#define QUEUE_H

class Queue {

  struct elem {
    elem* next;
    Node* node;
  };

 public:

  //Queue Constructor
  Queue();

  //Add an element to the queue
  void push(Node*);

  //Remove first element from the queue
  Node* pop();

  //Return length of queue
  int getSize();
  
  //Destructor
  ~Queue();
  
 private:

  //Head of queue
  elem* head;
  int size;

};
    
#endif
