#include <iostream>
#include <cstdlib> // for random
using namespace std;

// REMEMBER TO FIND ANOTHER WAY TO DO THIS!
// THIS IS A MEMORY LEAK!

char* random_first_name(int id){
  // returns a random first name (using id as a seed)
  static char names[][18] = {
    "Anita",
    "James",
    "Caleb",
    "Mary",
    "Stan",
    "Lucille",
    "Kayla",
    "Daniel",
    "Gina",
    // i give up on trying to think of names
    "Stork",
    "Basketball",
    "Walter",
    "Bone",
    "Tennis",
    "Gordon",
    "Patricia",
    "Minced",
    "Elbow",
  };
  srand(id);
  int index = rand() % 18;
  static char* name = names[index];
  return name;
}
