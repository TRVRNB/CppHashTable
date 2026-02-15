#ifndef LASTNAMES
#define LASTNAMES
#include <iostream>

// this is the only way that i currently know how to store names in a json-like file
class LastNames {
  public:
  static const int amount = 38;
  char names[amount][21] = {
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
    "Revolution",
    "Collector",
    "Young",
    "Washington",
    "Suggestion",
    "Ponytail",
    "Intention",
    "Unicorn",
    "Guitar",
    "Bass",
    "Chimichanga",
    "Actor",
    "Podcast",
    "Daugherty",
    "Driver",
    "Under The Stars",
    "Failure",
    "the Second",
    "Explanation",
    "Philosopher",
    "Housing",
    "Salad",
  };
};
#endif
