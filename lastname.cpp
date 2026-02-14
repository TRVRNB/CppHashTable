#include <iostream>
#include <cstdlib> // for random
using namespace std;

char* random_last_name(int id){
  // returns a random last name (using id as a seed)
  static char names[][16] = {
    // it's too late to try to remember names off the top of my head
    "Jabłonski",
    "Abrakadabra",
    "Johnson",
    "Lastname",
    "Tucker",
    "Atishon",
    "Roland",
    "Gumshoe",
    "Teatree",
    "Campbell",
    "Sicily",
    "Greece",
    "Turkey",
    "Egypt",
    "Myanmar",
    "Macaroni",
  };
  srand(id);
  int index = rand() % 16;
  static char* name = names[index];
  return name;
}
