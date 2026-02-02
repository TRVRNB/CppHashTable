#ifndef STUDENT
#define STUDENT
#include <iostream>
using namespace std;

// student class
class Student {
  public:
    char* name1 = new char[81]; // first name
    char* name2 = new char[81]; // last name
    int id = -42; // ID
    float gpa = -21.00; // GPA 
    ~Student();
  private:

};

#endif
