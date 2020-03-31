/*

C  2 0 4 8  console puzzle game

c2048.c

base game data types and functions

*/

#include <curses.h>
#include <unistd.h>

#include "c2048.h"

program_state game_play()
{
  erase();
  printw("c2048 game_play function");
  refresh();
  sleep(5);
  return state_exit;
}