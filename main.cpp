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

namespace studentlist {
  // public objects for this program
  char version[20] = "3.04";
  int starting_id = 10000;
  int ending_id = 10000;
  int entrySize;
  int tableSize = 100;
  const int maxTableSize = 512000; // if the hash table still doesn't fit, the program must quit. ignoring the students themselves, this hash list would be on the low end 100 megabytes (according to my very broad math); a few more recursions and there would be no memory left!
  Node** hashTable = new Node*[100](); // this should create a bunch of default nodes
  Node* headptr = new Node(nullptr); // DELETE THIS LATER! this is from the OLD program!
}
using namespace studentlist;

// HASH FUNCTIONS
void get_hashTable_size(){
  // this function is mostly irrelevant now; tableSize is tracked manually
  cout << "Table size: " << tableSize;
  int estimated_size = 280 * tableSize;
  cout << ", estimated size: " << estimated_size << " bytes." << endl;
  return;
}

int id_position(int id, int hashTable_size){
  // gets the position of a node, using its ID, in the array.
  // hashTable_size should use sizeof(hashTable) / sizeof(HashTable[0])
  // ALSO: sizeof(HashTable[0]) can be a constant value, since it's just a ptr
  // i think pointer sizes depend on the system and compiler, so it should be constant throughout the program
  // (unless the user is hot-swapping their RAM)
  if (id > ending_id){
    return -1; // this tells it to look for the next available slot in the hash table
  }
  return (id - starting_id) % tableSize;
}

float alphabetical_position(char*str){
  // takes a char / char array and returns a float, from 0.0 to 1.0, of its alphabetical position
  // (assuming student names start with capital letters)
  // since the hash table needs to be indexed using IDs, this function might not be used
  char abc[55] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  const char* str2 = &str[0];
  for (int i = 0; i<55; i++){
    const char* str1 = &abc[i];
    if (strcmp(str1, str2) == 0){
      return i / 56; // return its position, alphabetically, from 0.0 to 1.0
    }
  }
  return 1.0; // everything else is pushed to the back, alphabetically
}

int add_student_to_hashTable(Student* student, int recursion){
  // the mammoth function
  // adds a student to HashTable
  // and, if it would need more than 3 collisions, make hashTable twice as big.
  // it will be recursive, but only the first recursion will be able to change HashTable's size
  // CODES:
  // 0 - success
  // 1 - not enough room, double hashTable's size (first recursion won't call this)
  // 2 - error: >3 loops
  // 3 - error: maxTableSize exceeded, halt program
  // 4 - infinite recursions
  // 5 - other
  Node* new_node = new Node(student);
  int index = id_position(student->id, tableSize);
  bool RESIZE = false; // whether or not to resize the table later
  if (index == -1){ // this means it's a new student, instead of an old one being repositioned
    if (student->id > ending_id){
      ending_id = student->id;
    }
    Node* current_node = hashTable[0];
    bool found_end = false;
    bool in_bounds = true;
    int current_index = 0;
    int collision = 0;
    while (!found_end && in_bounds){ // basically, searches for an empty slot
      if (collision > 2){ // if the end of a chain is reached
	current_index += 1;
	if (current_index < tableSize){
	  current_node = hashTable[current_index];
	} else {
	  RESIZE = true;
	}
	collision = 0;
      } else { // if not at the end of a chain
	if ((current_node->getNext() == nullptr) && collision < 3){ // if there is room here
	  found_end = true;
	} else {
	  current_node = current_node->getNext();
	  collision += 1;
	}
      }
    }
    // end of searching for room
    if (!RESIZE){
      current_node->setNext(new_node); // append this node
      return 0; // good job
    }
  } else { // specific index
    Node* current_node = hashTable[index];
    int collision = 0;
    while (collision < 2 && (current_node->getNext() != nullptr)){
      current_node = current_node->getNext();
      collision += 1;
    }
    if (collision >= 2){
      RESIZE = true;
    } else {
      current_node->setNext(new_node);
    }
  } // emacs keeps trying to put an extra tab here for some reason!
  // RESIZING (mammoth function: part 2!)
  // WIP!
  if (RESIZE && recursion == 1){ // only run this on first recursion
    int unwrapped_index = 1;
    Student* unwrapped_hashTable[3*tableSize + 1]; // unwrap this hash table into a giant array
    for (int current_index = 0; current_index < tableSize; current_index++){
      Node* current_node = hashTable[current_index];
      for (int i = 0; i < 3; i++){
	// look for up to 3 collisions to add to the unwrapped list
	if (current_node != nullptr){
	  unwrapped_hashTable[unwrapped_index] = current_node->getStudent();
	  unwrapped_index++;
	  current_node = current_node->getNext();
	}
      }
    }
    // delete old table
    Node** oldTable = hashTable;
    tableSize *= 2;
    hashTable = new Node*[tableSize]();
    delete[] oldTable;
    get_hashTable_size();
    // re-hash!
    
  }
  return 5;
}
  
// END OF HASH FUNCTIONS



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
  int id1 = 1 + ending_id; // automatically increment it!
  // the project description doesn't say that the ID has to be chosen by the user, this time
  // so i assumed i could make the ID be automatically chosen
  // this makes the hash sort much easier
  // since it's table-sorted, the user could create an ID that is so far off the median that it ruins the sorting algorithm
  ending_id = id1;
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
  get_hashTable_size();
  cout << "Hash Table Student List - Version " << version << endl;
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
