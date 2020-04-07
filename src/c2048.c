/*

C  2 0 4 8  console puzzle game

c2048.c

base game data types and functions

*/

#include <ncurses.h>
#include <unistd.h>

#include "ncurs_etc.h"
#include "c2048.h"

program_state game_play()
{
  clear();
  printw("c2048 game_play function");
  refresh();
  sleep(5);
  return state_exit;
}