#include "display.h"

void Display::init() {
  initscr();
  cbreak();
  curs_set(0);
  noecho();
  /*nodelay(this->mainw, TRUE);*/
  if (has_colors()) start_color();
  use_default_colors();
  /*init colors*/
  init_pair(RED, COLOR_RED, BACKGROUND);
  init_pair(GREEN, COLOR_GREEN, BACKGROUND);
  init_pair(BLUE, COLOR_BLUE, BACKGROUND);
  init_pair(CYAN, COLOR_CYAN, BACKGROUND);
  init_pair(PURPLE, COLOR_MAGENTA, BACKGROUND);
  init_pair(YELLOW, COLOR_YELLOW, BACKGROUND);
  init_pair(WHITE, COLOR_WHITE, BACKGROUND);
  init_pair(BLACK, COLOR_BLACK, BACKGROUND);

  this->mainw_width = COLS/2 - (COLS/8);
  this->leftw_width = COLS/8;
  this->rightw_width = COLS/2;
  this->preview_width = COLS/2 - (2/* *state.show_border*/);
  
  this->root = newwin(LINES, COLS, 0, 0);
  this->leftw = newwin(LINES-1, this->leftw_width, 1, 0);
  this->mainw = newwin(LINES-1, this->mainw_width, 1, this->leftw_width);
  this->rightw = newwin(LINES-1, this->rightw_width, 1, COLS/2);
  this->titlew = newwin(LINES-1, this->width, 0, 0);
  this->previeww = newwin(LINES-1, this->preview_width, 1, COLS/2/* +state.show_border*/);
  
  wattron(this->leftw, COLOR_PAIR(BORDERCOLOR));
  wattron(this->mainw, COLOR_PAIR(BORDERCOLOR));
  wattron(this->rightw, COLOR_PAIR(BORDERCOLOR));
  wattron(this->titlew, COLOR_PAIR(TITLECOLOR));
  wattron(this->mainw, A_BOLD);
  wattron(this->leftw, A_BOLD);
  wattron(this->rightw, A_BOLD);
  wattron(this->titlew, A_BOLD);
}

void Display::update() {
  werase(this->mainw);
  wattron(this->mainw, COLOR_PAIR(BORDERCOLOR));
  box(this->mainw, 0, 0);
  wattroff(this->mainw, COLOR_PAIR(BORDERCOLOR));
  wrefresh(this->mainw);
}

bool Display::should_update(unsigned long tick) {
  return (tick % 10000000 == 0 && tick != 0) ? true : false;
}
