#ifndef NETWORKING_CLASS_H
#define NETWORKING_CLASS_H

#include <stdint.h>

class NetworkModule {
  private: 
  
  char host[64];
  char meathod[64];
  int portno;
  
  public:
  
  void init(char *host, char *meathod, int portno);
  void error(const char *msg);
  void print();

  void send_packet(char *file, char *path, int iid);
 /* 
  NetworkModule(char *host, char *meathod, int portno) {
    this->host = host;
    this->meathod = meathod;
    this->portno = portno;
  }*/
};

#endif
