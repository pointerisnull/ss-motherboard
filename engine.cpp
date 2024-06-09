#include "engine.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

char *read_file(const char* path) {
  FILE *file = fopen(path, "rb");
  if (!file) {
    perror("Error opening file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  unsigned long fsize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fsize + 1); // +1 for \0
  if (!buffer) {
    perror("Memory allocation failed");
    fclose(file);
    return NULL;
  }

  size_t bytesRead = fread(buffer, 1, fsize, file);
  if (bytesRead != fsize) {
    perror("Error reading file");
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[fsize] = '\0';

  fclose(file);
  return buffer;
}
//return without allocating memeory please
char *parse_config(char* buffer, const char* key) {
  const char* line = buffer;
  size_t key_len = strlen(key);

  while ((line = strstr(line, key)) != NULL) {
    if (line == buffer || line[-1] == '\n') {
      line += key_len;
      if (*line == '=') {
        line++;
        const char *value_end = strchr(line, '\n');
        if (value_end == NULL) {
          value_end = buffer + strlen(buffer);
        }
        size_t value_len = value_end - line;
        char *value = (char*)malloc((value_len + 1) * sizeof(char));
        //char value[1024];
        if (value != NULL) {
          strncpy(value, line, value_len);
          value[value_len] = '\0';
          return value;
        }
        free(value);
      }
    }
    line++;
  }
  return NULL;
}

void Engine::init() {
  char *buffer = NULL;
  char *host = NULL;
  char *port = NULL;
  char *meth = NULL;
  char *auth = NULL;

  is_running = 1;
  set_tick(0);
  /* if config file exists, open and read. */
  if (access("spacespotter/ss.config", F_OK) == 0) {
    //read config file
    buffer = read_file("spacespotter/ss.config");
    host = parse_config(buffer, "SERVER");
    port = parse_config(buffer, "PORT");
    meth = parse_config(buffer, "MEATHOD");
    auth = parse_config(buffer, "AUTH");
    printf("found: %s, %s, %s, %s\n", host, port, meth, auth);
    
    free(buffer);
  /* else generate default config */
  } else {
    printf("There was a problem reading the configuration file,\nUsing default configuration.\n");
    mkdir("spacespotter", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    FILE *file = fopen("spacespotter/ss.config", "w");
    fwrite(Engine::config_default, sizeof(char), strlen(Engine::config_default), file);
    fclose(file);
    printf("Generated a new configuration file.\n");
  }   
  /*initialize engine network module*/
  //if NULL values or no config file
  int portno = (port == NULL) ? 80 : atoi(port);
  char *n_host = (host == NULL) ? (char *)"127.0.0.1" : host;
  char *n_meth = (meth == NULL) ? (char *)"POST" : meth;
  //char *n_auth = (auth == NULL) ? (char *)"NULL" : auth;
  this->netmod.init(n_host, n_meth, portno);

  if (host != NULL) free(host);
  if (meth != NULL) free(meth);
  if (auth != NULL) free(auth);
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

void Engine::make_update_packet(char *file, int iid, int lot_ID, Space space) {
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
  fprintf(fp, "\"TIMETAKEN\":%ld,", space.timestamp);
  fprintf(fp, "\"POPULARITY\":%d", space.popularity);
  fprintf(fp ,"}");

  fclose(fp);
}

bool Engine::should_ping() {
  return (get_tick() % 100000000 == 0 && get_tick() != 0) ? true : false;
}

void Engine::ping_update(char *packet_path) {
  //std::cout << "Ping at " << get_tick() << std::endl;
  this->netmod.send_packet(packet_path, (char *) "spacespotter", 0);
}

void Engine::debug_print() {
  cout << "In netmodule: ";
  this->netmod.print();
}
