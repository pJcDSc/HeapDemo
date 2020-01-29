/*
Author: Peter Jin
Date: 1/11/20
Heap demo main class
*/

#include "Node.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
  cout << "Welcome to Heap demo. Type \"m\" for manual input or \"f\" for file input" << endl;
  char input;
  char* line;
  bool accept = false;
  while (!accept) {
    cin >> input;
    cin.clear();
    cin.ignore(999, '\n');
    if (input == 'f') {
      cout << "Input file name" << endl;
      char* fileName; cin.get(fileName, 99); cin.clear(); cin.ignore(999, '\n');
      cout << "Reading from \"" << fileName << "\"" << endl;
      ifstream fileStream (fileName);
      if (fileStream.is_open()) {
	fileStream.getline(line, 99);
      }
      else {
	cout << "Could not read from file" << endl;
	return 0;
      }
      fileStream.close();
      accept = true;
    }
    else if (input == 'm') {
      accept = true;
      cout << "Please enter a space separated list of integers" << endl;
      cin.get(line, 999); cin.clear(); cin.ignore(999, '\n');
    }
    else {
      cout << "Please enter either \"m\" for manual input or \"f\" for file input" << endl;
    }
  }
}
