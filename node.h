#ifndef NODE
#define NODE
#include "student.h"

class Node {
 public:
  Node(Student* init);//When a node is made sets the initial value and sets the next to NULL
  ~Node();//Deletes the memory location of the student and sets next to null
  Student* getStudent();//Gets the student
  void setNext(Node* newnext);//Sets the next node
  Node* getNext();//Gets the next node
 private:
  Student* student;//Value
  Node* next;//Next
};

#endif
