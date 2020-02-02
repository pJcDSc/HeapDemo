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

void makeHeap(Node* &head, char*); //Make a new heap out of head (NULL) and char* (space separated list of integers)
void addNode(Node* &head, char*); //Converts char* given to int, then adds a new node to the heap, re-sort
void reSort(Node* n); //Pass in most recently added node, moves to top based on heap insertion rules
void display(Node*, int);

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
  makeHeap(head, line);
  cout << endl << endl << endl;
  display(head, 0);
}

void makeHeap(Node* &head, char* line) {
  char* build = new char[strlen(line)](); //temp string to store individual words
  int ind = 0;
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] == ' ') { //Space found
      if (strlen(build) > 0) addNode(head, build); //Don't add empty
      build = new char[strlen(line)]();
      ind = 0;
    }
    else {
      if (isdigit(line[i])) build[ind++] = line[i]; //Don't add non-digits
    }
  }
  if (strlen(build) > 0) addNode(head, build);
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
      //display(head, 0);
      break;
    }
    if (!next -> getRight()) {
      next -> setRight(new Node(num));
      next -> getRight() -> setParent(next);
      reSort(next -> getRight());
      //display(head, 0);
      break;
    }
    q.push(next -> getLeft());
    q.push(next -> getRight());
  }
}

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
  if (n -> getLeft()) display(n -> getLeft(), d+1);
  for(int i = 0; i < d; i++) cout << "-  ";
  cout << n -> getValue() << endl;
  if (n -> getRight()) display(n -> getRight(), d+1);
}
