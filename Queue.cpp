/*
Author: Peter Jin
Date: 2/1/20
Heap Demo Queue Class
*/

#include "Queue.h"
#include "Node.h"
#include <iostream>

//Constructor
Queue::Queue() {
  head = NULL;
  size = 0;
}

//push an elem into queue
void Queue::push(Node* n) {
  size++;
  if (!head) {            //empty queue
    head = new elem();
    head -> node = n;
    return;
  }
  elem* temp = head;
  while (temp -> next) { //go to end of queue
    temp = temp -> next;
  }
  elem* e = new elem();   //add to end of queue
  temp -> next = e;
  e -> node = n;
  return;
}

//pop first element from queue
Node* Queue::pop() {
  if (!head) return NULL; //empty queue
  size--;                 //If we are popping size is decreased
  Node* temp = head -> node;
  elem* tempe = head;
  head = head -> next;
  delete tempe;
  return temp;
}

//Return the size, which we are keeping track of by adding or subtracting while pushing or popping
int Queue::getSize() {
  return size;
}

//destructor
Queue::~Queue() {
  while (head) {
    elem* temp = head;
    head = head -> next;
    delete temp;
  }
}
  
 
    
    
