#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include "net.h"
#include "lot.h"
#include <stdint.h>
#include <string>

class Engine {
private:
  uint64_t ticks;
  NetworkModule netmod;

public:
  char *config_default = (char *) 
    "SERVER=127.0.0.1\nPORT=80\nMEATHOD=POST\nAUTH=NULL";
  char *update_path = (char *)
    "spacespotter/update.JSON";
  char *init_path = (char *)
    "spacespotter/init.JSON";
  uint8_t is_running;
  
  void init();
  void tick();
  uint64_t get_tick();
  void set_tick(uint64_t setter);
  void check_events();
  bool should_ping();
  void make_initial_packet(char *file, int iid, Lot lot);
  void make_update_packet(char *file, int iid, int lot_ID, Space space);
  void ping_update(char *packet_path);

  void debug_print();

  Engine() { init(); }
};

#endif
