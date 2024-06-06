#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <stdint.h>
#include "net.h"
#include "lot.h"

class Engine {
private:
    uint64_t ticks;

public:
  char *config_default = (char *) 
    "SERVER=\nPORT=80\nMEATHOD=POST\nAUTH=";
  uint8_t is_running;

  void init(char *title);
  uint64_t get_tick();
  void set_tick(uint64_t setter);
  void tick();

  void check_events();
  bool should_ping();
  void make_initial_packet(char *file, int iid, Lot lot);
  void make_update_packet( char *file, int iid, int lot_ID, Space space, unsigned long time_taken);
  void ping_updates();

  Engine(char *title) {
    init(title);
  }
};

#endif
