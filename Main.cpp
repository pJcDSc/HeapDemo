/*
Author: Peter Jin
Date: 1/11/20
Heap demo main class
*/

#include "Node.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
  cout << "Welcome to Heap demo. Type \"m\" for manual input or \"f\" for file input" << endl;
  char input;
  
  bool accept = false;
  while (!accept) {
    cin >> input;
    cin.clear();
    cin.ignore(999, '\n');
    if (input == 'f') {
      accept = true;
      cout << "Please enter file name" << endl;
    }
    else if (input == 'm') {
      accept = true;
      cout << "Please enter a space separated list of integers" << endl;
    }
    else {
      cout << "Please enter either \"m\" for manual input or \"f\" for file input" << endl;
    }
  }
}
