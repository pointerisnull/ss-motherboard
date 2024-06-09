#include "lot.h"
#include <iostream>
#include <cstdlib> 
#include <time.h>

void Space::update() {
  this->is_occ = !this->is_occ;
  this->timestamp = time(NULL);
  if (this->is_occ) 
    this->popularity++;
}

void Space::print() {
  std::cout << "space id: " << id 
  << " is taken: " << is_occ << std::endl;
}

int Lot::space_count() {
  return (int) spaces.size();
}

Space Lot::get_space(int i) {
  return this->spaces[i];
}

void Lot::update_space(int i) {
  this->spaces[i].update();
}

void Lot::debug_randomize(int ittr) {
  srand(time(NULL)); // seed the random number generator
  for (int i = 0; i < ittr; i++) {
    int space = rand() % this->spaces.size();
    update_space(space);
  }
}

void Lot::debug_clear() {
  for (int i = 0; i < (int) this->spaces.size(); i++) {
    this->spaces[i].is_occ = false;
    this->spaces[i].timestamp = 0;
    this->spaces[i].popularity = 0;
  }
}

void Lot::print() {
  for (int i = 0; i < space_count(); i++) {
    spaces[i].print();
  }
}
