/*
Author: Peter Jin
Date: 1/11/20
Heap demo main class
*/
#include "Node.h"
#include "Queue.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int makeHeap(Node* &head, char*); //Make a new heap out of head (NULL) and char* (space separated list of integers)
void addNode(Node* &head, char*); //Converts char* given to int, then adds a new node to the heap, re-sort
void reSort(Node* n); //Pass in most recently added node, moves to top based on heap insertion rules
void display(Node*, int); //Displays heap (horizontally) using infix trasversal
int deleteNode(Node* &head, int); //Passes in binary int as path (1 is right, 0 is left); returns deleted value
void heapify(Node* n); //Takes top node and moves it downward (used in delete)

int main() {
  cout << "Welcome to Heap demo. Type \"m\" for manual input or \"f\" for file input" << endl;
  char input;
  char* line;
  bool accept = false;
                                                    //Reading in input now from console or from file
  while (!accept) {
    cin >> input;
    cin.clear();
    cin.ignore(999, '\n');
    if (input == 'f') {                             //File input
      cout << "Input file name" << endl;
      char* fileName; cin.get(fileName, 500);
      cin.clear(); cin.ignore(999, '\n');
      cout << "Reading from \"" << fileName << "\"" << endl;
      ifstream fileStream (fileName);               //Get ifstream of file
      if (fileStream.is_open()) {
	fileStream.getline(line, 99);               //Read line from File
      }
      else {                                        //File is not readable
	cout << "Could not read from file" << endl;
	return 0;
      }
      fileStream.close();
      accept = true;
    }                                               //Console Input
    else if (input == 'm') {    
      accept = true;
      cout << "Please enter a space separated list of integers" << endl;
      cin.get(line, 500); cin.clear(); cin.ignore(999, '\n');
    }
    else {                                          //Input mode not accepted
      cout << "Please enter either \"m\" for manual input or \"f\" for file input" << endl;
    }
  }

  Node* head = NULL;
  
  cout << "Creating Heap..." << endl;
  int heapLen = makeHeap(head, line);               //Store length of heap (to get last node in o(logn) time) and create heap
  display(head, 0);
  cout << endl;
  cout << "Deleting heap..." << endl;
  while (heapLen > 0) {
    cout << deleteNode(head, heapLen--);
    if (heapLen > 0) cout << ", ";
  }
  cout << endl;
}

int makeHeap(Node* &head, char* line) {
  char* build = new char[strlen(line)+1]();          //temp string to store individual words
  int len = 0;
  int ind = 0;
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] == ' ') { //Space found
      if (strlen(build) > 0) {
	addNode(head, build); //Don't add empty
	len ++;
      }
      build = new char[strlen(line)]();
      ind = 0;
    }
    else {
      if (isdigit(line[i])) build[ind++] = line[i]; //Don't add non-digits
    }
  }
  if (strlen(build) > 0) {
    addNode(head, build);
    len ++;
  }
  return len;
}

void addNode(Node* &head, char* nc) {
  int num = 0;
  for(int i = 0; i < strlen(nc); i++) {             //build num
    num *= 10;
    num += nc[i]-'0';
  }

  if (!head) {                                      //if list is empty
    head = new Node(num);
    return;
  }
  
  Queue q; //Haha get it q ('queue')
  q.push(head); 
  while (q.getSize() > 0) {                         //Level traverse / bfs using queue 
    Node* next = q.pop();
    if (!next -> getLeft()) {                       
      next -> setLeft(new Node(num));
      next -> getLeft() -> setParent(next);
      reSort(next -> getLeft());
      break;
    }
    if (!next -> getRight()) {
      next -> setRight(new Node(num));
      next -> getRight() -> setParent(next);
      reSort(next -> getRight());
      break;
    }
    q.push(next -> getLeft());
    q.push(next -> getRight());
  }
}

//takes a node at(or near) the bottom and switches it with its parent if it is bigger
void reSort(Node* n) {
  if (!n || !n -> getParent()) return;              //1 or empty node list
  if (n -> getParent() -> getValue() <
      n -> getValue()) {                            //swap da values
    int val = n -> getValue();
    n -> setValue(n -> getParent() -> getValue());
    n -> getParent() -> setValue(val);
    reSort(n -> getParent());
  }
  return;
}

//Display using sideways print based on infix navigation
void display(Node* n, int d) {
  if (!n) return;                                  //empty heap
  if (n -> getLeft()) display(n -> getLeft(), d+1);
  for(int i = 0; i < d; i++) cout << "   ";
  cout << n -> getValue() << endl;
  if (n -> getRight()) display(n -> getRight(), d+1);
}

//Delete head, return it
int deleteNode(Node* &head, int path) {
  if (!head) {
    return NULL;                                   //List is empty
  }
  Node* lastNode = head;
  
  int rev = 0;
  int len = -1;                                    //We remove one digit at the end
  while (path > 0) {                               //invert path (if path was 1100101 in binary, now is 1010011)
    rev *= 2;
    rev += path % 2;
    path /= 2;
    len++;
  } 
  path = rev / 2;                                  //Remove last digit of binary, because in original binary we disregard it
  while (len-- > 0) {
    if (path % 2 == 1) {                           //if odd go right
      lastNode = lastNode -> getRight();
    }
    else {
      lastNode = lastNode -> getLeft();
    }
    path /= 2;
  }

  if (lastNode == head) {                           //One node list
    Node* temp = head;
    int ret = head -> getValue();
    head = NULL;
    delete temp;
    return ret;
  }

  int ret = head -> getValue();
  head -> setValue(lastNode -> getValue());
  if (lastNode -> getParent() -> getRight() == lastNode) {
    lastNode -> getParent() -> setRight(NULL);
  } else {
    lastNode -> getParent() -> setLeft(NULL);
  }
  delete lastNode;
  heapify(head);
  return ret;
}

//Pass in head, switch it down
void heapify(Node* head) {
  Node* switchNode = NULL;
  if (head -> getRight() && head -> getValue() < head -> getRight() -> getValue()) { //Check if any of the children are bigger, and if so which one is bigger
    switchNode = head -> getRight();
  }
  if (head -> getLeft() && head -> getValue() < head -> getLeft() -> getValue()) {
    if (!switchNode || switchNode -> getValue() < head -> getLeft() -> getValue()) switchNode = head -> getLeft(); //check which child is larger
  }

  if (!switchNode) return; //No children bigger
  int temp = switchNode -> getValue();
  switchNode -> setValue(head -> getValue());
  head -> setValue(temp);
  heapify(switchNode);
}
