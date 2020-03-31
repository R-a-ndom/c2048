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
#include "title_scr.h"

int main()
{
  program_state game_state;
  initscr();

  game_state = game_title_screen();

  if ( game_state == state_begin )
  {
     game_play();
  }

  endwin();
  return(EXIT_SUCCESS);
}