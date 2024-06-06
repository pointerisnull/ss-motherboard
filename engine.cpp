#include "engine.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>

void Engine::init(char *title) {
  is_running = 1;
  set_tick(0);
  /* if config file exists, open and read. */
  if (FILE *file = fopen("spacespotter/ss.config", "r")) {
    //read config file
    fclose(file);
  /* else generate default config */
  } else {
    printf("There was a problem reading the configuration file,\nUsing default configuration.\n");
    mkdir("spacespotter", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    file = fopen("spacespotter/ss.config", "w");
    fwrite(Engine::config_default, sizeof(char), strlen(Engine::config_default), file);
    //set configuration here
    fclose(file);
    printf("Generated a new configuration file.\n");
  }   
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
   */
}
/*
 * for now, packets are stored locally as a file
 * (debug purposes), store in a buffer later
 */
void Engine::make_initial_packet(char *file, int iid, Lot lot) {
  
  FILE *fp = fopen(file, "w");
	if(fp == NULL) {
		printf("error saving JSON!\n");
	}
  fprintf(fp, "{");
  fprintf(fp, "\"IID\":%d,", iid);
  fprintf(fp, "\"LOTID\":%d,", lot.id);
  fprintf(fp, "\"SPACES\":[");
  for(int j = 0; j < lot.space_count()-1; j++) {
    fprintf(fp, "%d,", lot.get_space(j).is_occ);
  }
  fprintf(fp, "%d", lot.get_space(lot.space_count()-1).is_occ);

  fprintf(fp, "]");
  fprintf(fp ,"}");

  fclose(fp);

}

void Engine::make_update_packet(char *file, int iid, int lot_ID, Space space, unsigned long time_taken) {
	FILE *fp = fopen(file, "w");
	if(fp == NULL) {
		printf("error saving JSON!\n");
	}
  uint64_t current_time = time(NULL);
  fprintf(fp, "{");
  fprintf(fp, "\"IID\":%d,", iid);
  fprintf(fp, "\"TIME\":%ld,", current_time);
  fprintf(fp, "\"STATUS\":%d,",space.is_occ);
  fprintf(fp, "\"LOTID\":%d,", lot_ID);
  fprintf(fp, "\"SPACEID\":%d,", space.id);
  fprintf(fp, "\"TIMETAKEN\":%ld,", time_taken);
  fprintf(fp, "\"POPULARITY\":%d", space.popularity);
  fprintf(fp ,"}");

  fclose(fp);
}

bool Engine::should_ping() {
  return (get_tick() % 100000000 == 0 && get_tick() != 0) ? true : false;
}

void Engine::ping_updates() {
  std::cout << "Ping at " << get_tick() << std::endl;
}
