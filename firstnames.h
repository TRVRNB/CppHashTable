#ifndef FIRSTNAMES
#define FIRSTNAMES
#include <iostream>

// this is the only way that i currently know how to store names in a json-like file
class FirstNames {
  public:
  static const int amount = 45;
  char names[amount][21] = { // max character length of 21. obviously we live in the 80's so i need to conserve extremely tiny amounts of memory!
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
    "Debt",
    "Reading",
    "Reese",
    "Champ",
    "Cupcake",
    "Satisfactory",
    "Incoming",
    "Society",
    "President",
    "Major",
    "Seargent",
    "Colonel",
    "Officer",
    "Secret Agent",
    "Best Buy Employee",
    "Piano",
    "Incense",
    "Coffee",
    "Temperate",
    "Love",
    "Television",
    "Greek",
    "Floppy",
    "Polish",
    "Low-Income",
    "Genetic",
    "Tooth",
  };
};
#endif
