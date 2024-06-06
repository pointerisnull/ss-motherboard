#include "lot.h"
#include <iostream>

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

void Lot::print() {
  for (int i = 0; i < space_count(); i++) {
    spaces[i].print();
  }
}
