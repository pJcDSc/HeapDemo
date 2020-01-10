/*
Author: Peter Jin
Date: 1/10/20
Heap demo node header 
*/

#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {

 public:

  //Constructor
  Node(int);

  //Set value of node
  void setValue(int);

  //Get pointer to left node
  Node* getLeft();

  //Set left node
  void setLeft(Node*);

  //Get pointer to right
  Node* getRight();

  //Set right node
  void setRight(Node*);
  
  //Get value of node
  int getValue();

  //Destructor
  ~Node();