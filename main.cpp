// The hash table will start out with a size of 200.
// The entries will be linked lists. The head pointer to this linked list could be blank; maybe this will make it easier to DELETE the first student.
// Do keys HAVE to have data? They could be sorted alphabetically, which would make them easy to stretch out over a large array.
// The keys could also just represent their position in the array. So the 31st key would just be labelled "31".
// I need to make a function that gets a float value based on text's alphabetical position, assuming student names always start with capital letters.
#include <iostream>
#include <cstring> // for strcmp()
#include <cstdlib> // for strtol() + strtof()
#include <cmath> // for round()
#include "student.h"
#include "node.h"
using namespace std;

float alphabetical_position(char*str){
  // takes a char / char array and returns a float, from 0.0 to 1.0, of its alphabetical position
  char abc[28] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char* str2 = &str[0];
  for (int i = 0; i<28; i++){
    const char* str1 = &abc[i];
    if (strcmp(str1, str2) == 0){
      return i / 28; // return its position, alphabetically, from 0.0 to 1.0
    }
  }
  return 1.0; // everything else is pushed to the back, alphabetically
}

// NODE FUNCTIONS
void node_add_student(Student*student, Node*ptr){
  // adds student to the end of the linked list
  if (ptr->getNext() == nullptr){
    Node* newptr = new Node(student);
    ptr->setNext(newptr);
  } else {
    node_add_student(student, ptr->getNext());
  }
}

void print_remaining(Node*ptr, int i){
  // prints the next node and all the nodes after it
  if (ptr == nullptr){
    return;
  }
  // this part only runs if the pointer exists
  Student* student = ptr->getStudent();
  cout << i << ") ";
  cout << student->name1 << ' ' << student->name2 << ", ";
  cout << student->id << ", ";
  cout << student->gpa << "\n";
  i++;
  print_remaining(ptr->getNext(), i);

}

float average(Node*ptr, float total, int count){
  // add up the average and divide by count if it's the last one
  if (ptr == nullptr){
    if (count == 0){ // avoid division by 0
      return 0;
    }
    float average = round((total / count) * 100) / 100;
    return average;
  }
  total += ptr->getStudent()->gpa;
  return average(ptr->getNext(), total, count+1);
}
// END OF NODE FUNCTIONS

void print(const char* text = ""){
  // cout wrapper, similar to python print()
  cout << text << '\n' << flush;
  return;
}

char* input(const char* text = ""){
  // cin wrapper, similar to python input()
  cout << text << flush;
  char* input1 = new char[81]; // handle up to 80 chars (dynamically allocate, i actually forgot what this meant on the test)
  cin >> input1;
  return input1;
}

void add_student(){
  // adds a student based on user input
  char* pEnd; // this is needed for some low-level memory stuff in strtol and strtof
  char name1[81]; strcpy(name1, input("Enter the student's first name: ")); // does this break style? the function was already bulky so i wanted to combine like terms
  char name2[81]; strcpy(name2, input("Enter the student's last name: "));
  char* id = input("Enter the student ID: ");
  int id1 = strtol(id, &pEnd, 10); // cast to int
  char* gpa = input("Enter the student's GPA: ");
  float gpa1 = strtof(gpa, &pEnd); // cast to float
  float gpa2 = round(100 * gpa1) / 100; // round to 2 decimal points
  Student* student = new Student; // to keep it in memory after this scope ends; be sure to free this memory when it gets deleted
  strcpy(student->name1, name1);
  strcpy(student->name2, name2);
  student->id = id1; // id
  student->gpa = gpa2; // gpa
  node_add_student(student, headptr); // new function
  return;
}

void print_students(){
  // print the students that are stored
  print("Student list:");
  short i = 1;
  Node* ptr = studentlist::headptr;
  print_remaining(headptr->getNext(), i);
  cout << flush;
  return;
}

void delete_student_with_id(Node* lastptr, Node* ptr, int id){
  // try to delete this student, or move on to the next
  Student* student = ptr->getStudent();
  if (student->id == id){
    cout << "Removing " << student->name1 << ' ' << student->name2 << "..." << endl;
    lastptr->setNext(ptr->getNext());
    delete ptr;
  } else {
    if (ptr->getNext() == nullptr){
      cout << "Student not found." << endl;
      return;
    }
    delete_student_with_id(ptr, ptr->getNext(), id);
  }
}

void delete_student(){
  // remove a student at a point
  print_students();
  char* pEnd;
  char* indexstr = input("Enter the student ID to delete: ");
  int index = strtol(indexstr, &pEnd, 10); // cast to int
  Node* ptr = headptr->getNext();
  Node* lastptr = headptr;
  delete_student_with_id(lastptr, ptr, index); // new function
}
  
int main(){
  print("Student List - 10/9/25");
  print("Welcome! Type 'HELP' for a list of commands.");
  bool running = 1;
  while (running){ // main loop
    const char* cmd = input("$ ");
    // command list starts here
    if (strcmp(cmd, "HELP") == 0){ // HELP
      print("HELP: print list of commands");
      print("QUIT: quit this program");
      print("ADD: add a student");
      print("PRINT: print all the students currently stored");
      print("DELETE: delete a student");
      print("AVERAGE: get GPA average");
    }
    if (strcmp(cmd, "QUIT") == 0){ // QUIT
      running = 0; // program will stop after completing this loop
      print("Goodbye!");
    }
    if (strcmp(cmd, "ADD") == 0){ // ADD
      add_student();
    }
    if (strcmp(cmd, "PRINT") == 0){ // PRINT
      print_students();
    }
    if (strcmp(cmd, "DELETE") == 0){ // DELETE
      delete_student();
    }
    if (strcmp(cmd, "AVERAGE") == 0){ // AVERAGE
      float average1 = average(headptr->getNext(), 0, 0);
      cout << average1 << endl;
    }
  }
  return 0;
}
