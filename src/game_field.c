/*

C  2 0 4 8  console puzzle game

game_field.c

game field functions

*/

#include <ncurses.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "c2048.h"
#include "all_draws.h"

static const scr_point field_start = { 5, 2 };

/* --- +++ --- */

void init_game_field(game_field field)
{
  int i, j;
  for(i = 0; i <= field_size; i++)
    for(j = 0; j <= field_size; j++)
    {
       field[i][j].value = 0;
       field[i][j].color = 0;
    }
}

scr_point cell_draw_coords(int h_num, int v_num)
{
  scr_point tmp;
  tmp.row = field_start.row + h_num * ( cell_h_size + 1);
  tmp.col = field_start.col + v_num * ( cell_v_size + 1);
  return tmp;
}

void draw_game_field(WINDOW *win_field, game_field field)
{
  int i, j;
  scr_point draw_pos;
  for(i = 0; i <= field_size; i++)
    for(j = 0; j <= field_size; j++)
    {
      draw_pos = cell_draw_coords(i, j);
      wmove(win_field, draw_pos.row, draw_pos.col);
      wprintw(win_field, "%d", field[i][j].value);
    }
}