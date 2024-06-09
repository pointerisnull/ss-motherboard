#include <iostream>
#include "engine.h"
#include "display.h"
#include "lot.h"

int main() {
  Engine engine;
  engine.debug_print();

  Display disp;
  disp.init();
  
  Lot lot(0, 10);

  engine.make_initial_packet(engine.init_path, 0, lot);
  engine.ping_update(engine.init_path);

  while(engine.is_running) {
    engine.check_events();
    if (disp.should_update(engine.get_tick())) 
      disp.update();
    if (engine.should_ping()) { //testing
      lot.debug_randomize(30);
      engine.make_update_packet(engine.update_path, 0, 0, lot.get_space(5));
      engine.ping_update(engine.update_path);
    }
    engine.tick();
  }

  return 0;
}
