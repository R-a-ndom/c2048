/*

C  2 0 4 8  console puzzle game

all_draws.c

screen and windows drawing

*/

#include <ncurses.h>


void draw_grid(WINDOW* win_game_field)
{
  mvwaddch(win_game_field,0,0,'+');
}