#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "node.h"

using namespace std;

Node::Node(Student* init) {
  student = init;
  next = NULL;
}

Node::~Node() {
  // i removed the student destructor from here, INTENTIONALLY!
  next = NULL;
}

Student* Node::getStudent() {
  return student;
}

Node* Node::getNext() {
  return next;
}

void Node::setNext(Node* newnext) {
  next = newnext;
}
#endif
