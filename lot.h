#ifndef LOT_CLASS_H
#define LOT_CLASS_H

#include <stdint.h>
#include <vector>

class Space {
public:
  
  int id;
  bool is_occ;
  uint64_t time_taken;
  uint16_t popularity;

  void print();

  Space(int id) {
    this->id = id;
    this->is_occ = false;
    this->time_taken = 0;
    this->popularity = 0;
  }

};

class Lot {
private:
  
  std::vector<Space> spaces;

public:

  uint8_t id;

  void print();
  int space_count();
  void add(Space space);
  Space get_space(int i);
  
  void debug_randomize(int scount);
  void debug_clear();

  Lot(int id, int scount) {
    this->id = id;
    for (int i = 0; i < scount; i++)
      this->spaces.push_back(Space(i)); 
  }
};

#endif
