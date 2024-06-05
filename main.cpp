#include <iostream>
#include "engine.h"
#include "net.h"

int main() {
    Engine engine((char *) "Space Spotter 2024");
    NetworkModule net((char *)"10.64.128.73", (char *)"POST", 80);
    net.print();

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
