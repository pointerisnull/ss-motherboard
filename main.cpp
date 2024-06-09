#include <iostream>
#include "engine.h"
#include "net.h"
#include "lot.h"

int main() {
  Engine engine;
  engine.debug_print();
  
  Lot lot(0, 10);
  lot.debug_randomize(30);
  lot.print();

  engine.make_initial_packet(engine.init_path, 0, lot);
  engine.ping_update(engine.init_path);

  while(engine.is_running) {
  engine.check_events();
    if (engine.should_ping()) { //testing
      lot.debug_randomize(30);
      engine.make_update_packet(engine.update_path, 0, 0, lot.get_space(5));
      engine.ping_update(engine.update_path);
    }
    engine.tick();
  }

  return 0;
}
