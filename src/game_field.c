/*

C  2 0 4 8  console puzzle game

game_field.c

game field functions

*/

#include <stdlib.h>
#include <ncurses.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "c2048.h"
#include "all_draws.h"

static const scr_point field_start = { 5, 2 };

const double max_rand_num = 100.0;
const int border_rand_num =    90;

/* --- +++ --- +++ --- +++ --- +++ --- *
 *     numbers and coords generaing    *
 * --- +++ --- +++ --- +++ --- +++ --- */

int new_field_number()
{
  int num;
  num = (int)(max_rand_num*rand()/(RAND_MAX + 1.0));
  if (num <= border_rand_num)
    return 2;
  else
    return 4;
}

/* --- +++ --- */

void get_new_num_coords(game_field field, int *h_coord, int *v_coord)
{
  int h_tmp, v_tmp;
  do {
    h_tmp = (int)((double)max_cell_num*rand()/(RAND_MAX + 1.0));
    v_tmp = (int)((double)max_cell_num*rand()/(RAND_MAX + 1.0));
  } while (field[h_tmp][v_tmp].value != 0);
  *h_coord = h_tmp;
  *v_coord = v_tmp;
}

/* --- +++ --- */

void add_new_cell(game_field field)
{
  int h_pos, v_pos;
  get_new_num_coords(field, &h_pos, &v_pos);
  field[h_pos][v_pos].value = new_field_number();
  if ( field[h_pos][v_pos].value == 2 )
    field[h_pos][v_pos].color = 1;
  else
    field[h_pos][v_pos].color = 2;
}

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

/* --- +++ --- +++ --- +++ --- +++ --- *
 *   drawing cells on field window     *
 * --- +++ --- +++ --- +++ --- +++ --- */

scr_point get_cell_draw_coords(int h_num, int v_num)
{
  scr_point tmp;
  tmp.row = field_start.row + h_num * ( cell_h_size + 1);
  tmp.col = field_start.col + v_num * ( cell_v_size + 1);
  return tmp;
}

/* --- +++ --- */


void draw_one_cell(WINDOW* win_field,
                   game_field field,
                   int h_pos, int v_pos)
{
  scr_point draw_pos = get_cell_draw_coords(h_pos, v_pos);

  if ( field[h_pos][v_pos].value == 0 )
  {
    wattrset(win_field, COLOR_PAIR(col_standard));
    wclear_rect(win_field,
                draw_pos,
                cell_h_size, cell_v_size);
  } else {
    wattrset(win_field, COLOR_PAIR(field[h_pos][v_pos].color));
    wclear_rect(win_field,
                draw_pos,
                cell_h_size, cell_v_size);
    wmove(win_field, draw_pos.row, draw_pos.col);
    wprintw(win_field, "%d", field[h_pos][v_pos].value);
  }
}

/* --- +++ --- */

void draw_game_field(WINDOW *win_field, game_field field)
{
  int i, j;
  for(i = 0; i <= field_size; i++)
    for(j = 0; j <= field_size; j++)
    {
      draw_one_cell(win_field, field, i, j);
    }
}

/* --- +++ --- +++ --- +++ --- +++ --- *
 *    manipulating with field array    *
 * --- +++ --- +++ --- +++ --- +++ --- */

void copy_field(game_field field_from, game_field field_to)
{
  int i,j;
  for(i = 0; i<= field_size; i++)
    for(j = 0; j<= field_size; j++)
    {
      field_to[i][j].value = field_from[i][j].value;
      field_to[i][j].color = field_from[i][j].color;
    }
}

/* --- +++ --- */

int there_are_free_cells(game_field field)
{
  int i,j;
  int check_flag = BOOL_FALSE;
  for(i = 0; i<= field_size; i++)
  {
    for(j = 0; j<= field_size; j++)
    {
      if (field[i][j].value == 0)
      {
        check_flag = BOOL_TRUE;
        break;
      }
    }
    if (check_flag == BOOL_TRUE)
    {
      break;
    }
  }
  return check_flag;
}