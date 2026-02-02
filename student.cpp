#include <iostream>
#include "student.h"
using namespace std;

// i probably only need this for the destructor
Student::~Student(){
  delete[] name1;
  delete[] name2;
  cout << "Student deleted." << endl;
}
