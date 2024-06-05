#include "engine.h"
#include <iostream>


void Engine::init(char *title) {
    is_running = 1;
    set_tick(0);
}

uint64_t Engine::get_tick() {
    return ticks;
}

void Engine::set_tick(uint64_t setter) {
    ticks = setter;
}

void Engine::tick() {
  ticks++;
}

void Engine::check_events() {
  /*
   * Check device input, separate thread??
  }*/
}

void Engine::make_initial_packet(char *file, int iid/*, Lot lot*/) {
  /*
  FILE *fp = fopen(fileName, "w");
	if(fp == NULL) {
		printf("error saving JSON!\n");
	}
  fprintf(fp, "{");
  fprintf(fp, "\"IID\":%d,", iid);
  fprintf(fp, "\"LOTID\":%d,", lot.id);
  fprintf(fp, "\"SPACES\":[");
  for(int j = 0; j < lot.spaceCount-1; j++) {
    fprintf(fp, "%d,", lot.space[j].isOccupied);
  }
  fprintf(fp, "%d", lot.space[lot.spaceCount-1].isOccupied);
  fprintf(fp, "]");
  fprintf(fp ,"}");

  fclose(fp);
*/
}

void Engine::make_update_packet(char *file, int iid, int is_occ, int lot_ID, int spot_ID, int popularity, unsigned long time_taken) {
	FILE *fp = fopen(file, "w");
	if(fp == NULL) {
		printf("error saving JSON!\n");
	}
  uint64_t current_time = time(NULL);
  fprintf(fp, "{");
  fprintf(fp, "\"IID\":%d,", iid);
  fprintf(fp, "\"TIME\":%ld,", current_time);
  fprintf(fp, "\"STATUS\":%d,",is_occ);
  fprintf(fp, "\"LOTID\":%d,", lot_ID);
  fprintf(fp, "\"SPACEID\":%d,", spot_ID);
  fprintf(fp, "\"TIMETAKEN\":%ld,", time_taken);
  fprintf(fp, "\"POPULARITY\":%d", popularity);
  fprintf(fp ,"}");

  fclose(fp);
}

bool Engine::should_ping() {
  return (get_tick() % 100000000 == 0 && get_tick() != 0) ? true : false;
}

void Engine::ping_updates() {
  std::cout << "Ping at " << get_tick() << std::endl;
}
