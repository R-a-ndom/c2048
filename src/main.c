/*

C  2 0 4 8  console puzzle game

main.c

main file

*/

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "ncurs_etc.h"
#include "c2048.h"
#include "all_draws.h"
#include "title_scr.h"

int main()
{
  program_state game_state;

  initscr();
  if ( !has_colors() )
  {
    fprintf(stderr, "C2048 -> Terminal cannot do colors!\n");
    fprintf(stderr, "Colors support required.\n");
    exit(1);
  }
  if ( start_color() != OK )
  {
    fprintf(stderr, "C2048 -> Unable to start colors!\n");
    fprintf(stderr, "Colors support required.\n");
    exit(2);
  }
#ifdef DEBUG
  init_pair(1, COLOR_RED, COLOR_BLACK);
  attrset(COLOR_PAIR(1));
  printw("C 2 0 4 8");
  napms(debug_mini_time);
#endif
  init_all_colors();

  game_state = game_title_screen();

  if ( game_state == state_begin )
  {
     game_play();
  }
  endwin();
  return(EXIT_SUCCESS);
}