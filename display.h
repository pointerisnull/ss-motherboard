#ifndef DISPLAY_CLASS_H
#define DISPLAY_CLASS_H

#include <ncurses.h>

#define TERMCOLOR -1
#define RED     1
#define GREEN   2
#define BLUE    3
#define CYAN    4
#define PURPLE  5
#define YELLOW  6
#define WHITE   7
#define BLACK   8

#define BACKGROUND    TERMCOLOR
#define BORDERCOLOR   GREEN
#define CURSORCOLOR   GREEN
#define TITLECOLOR    WHITE

class Display {
private:
  WINDOW *root;
  WINDOW *titlew;
  WINDOW *leftw;
  WINDOW *mainw;
  WINDOW *rightw;
  WINDOW *previeww;
  int mainw_width;
  int leftw_width;
  int rightw_width;
  int preview_width;
  int preview_height;
  int width, height;

public:
  void init();
  void check_updates();
  bool should_update(unsigned long tick);
  void update();
  void kill();

};

#endif
