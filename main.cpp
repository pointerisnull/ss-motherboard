#include <iostream>
#include "engine.h"
#include "net.h"
#include "lot.h"

int main() {
  Engine engine((char *) "Space Spotter 2024");
  NetworkModule net((char *)"bhaney.net"/*"10.64.128.73"*/, (char *)"POST", 80);
  net.print();

  Lot lot(0, 10);

  engine.make_initial_packet((char *)"spacespotter/init.JSON", 0, lot);
  std::cout << "sending packet now" << std::endl;
  net.send_packet((char *) "spacespotter/init.JSON", (char *) "spacespotter", 0);

  while(engine.is_running) {
  //std::cout << engine.get_tick() << std::endl;
  //engine.update_window();
  engine.check_events();
    if (engine.should_ping())
      engine.ping_updates();
    engine.tick();
  }

  return 0;
}
