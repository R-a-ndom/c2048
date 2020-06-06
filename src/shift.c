/*

C  2 0 4 8  console puzzle game

shift.c

game field shift functions

*/

#include <ncurses.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "game_field.h"
#include "shift.h"

/* cell manipulation functions */

void clear_cell(field_cell* cell)
{
  cell->value = 0;
  cell->color = 0;
}

void swap_cells(field_cell cell_from, field_cell cell_to)
{
  field_cell cell_tmp;
  cell_tmp = cell_to;
  cell_to = cell_from;
  cell_from = cell_tmp;
}

/* shifting functions */

void shift_field_left(WINDOW* win_field,
                      game_field field,
                      move_state state)
{
  int row_pos, col_pos;

  state.occuring = move_not_occured;
  for(col_pos = 0; col_pos <= field_size - 1; col_pos--)
  {
    for(row_pos = 0; row_pos <= field_size; row_pos++)
    {
    }
    draw_game_field(win_field, field);
    napms(draw_pause);
    wrefresh(win_field);
  }
}

void shift_field_right(WINDOW* win_field,
                       game_field field,
                       move_state state)
{
  int row_pos, col_pos;

  state.occuring = move_not_occured;
  for(col_pos = field_size; col_pos >= 1; col_pos--)
  {
    for(row_pos = 0; row_pos <= field_size; row_pos++)
    {
      if((field[row_pos][col_pos].value == 0) &&
         (field[row_pos][col_pos-1].value != 0))
      {
        swap_cells(field[row_pos][col_pos], field[row_pos][col_pos-1]);
      }
    }
    draw_game_field(win_field, field);
    napms(draw_pause);
    wrefresh(win_field);
  }
}

void shift_field_up(WINDOW* win_field,
                    game_field field,
                    move_state state)
{
  int row_pos, col_pos;

  state.occuring = move_not_occured;
  for(row_pos = 0; row_pos <= field_size - 1; row_pos--)
  {
    for(col_pos = 0; col_pos <= field_size; col_pos++)
    {

    }
    draw_game_field(win_field, field);
    napms(draw_pause);
    wrefresh(win_field);
  }


}

void shift_field_down(WINDOW* win_field,
                      game_field field,
                      move_state state)
{
  int row_pos, col_pos;

  state.occuring = move_not_occured;
  for(row_pos = field_size; row_pos >= 1; row_pos--)
  {
    for(col_pos = 0; col_pos <= field_size; col_pos++)
    {

    }
    draw_game_field(win_field, field);
    napms(draw_pause);
    wrefresh(win_field);
  }
}


/* game move function */

void game_move(WINDOW* win_field,
               chtype sym,
               game_field field,
               game_field field_backup,
               move_state m_state)
{
  switch (sym)
  {
    case KEY_LEFT:
    {
      shift_field_left(win_field, field, m_state);
      break;
    }

    case KEY_RIGHT:
    {
      shift_field_right(win_field, field, m_state);
      break;
    }

    case KEY_UP:
    {
      shift_field_up(win_field, field, m_state);
      break;
    }

    case KEY_DOWN:
    {
      shift_field_down(win_field, field, m_state);
      break;
    }
  }
  copy_field(field, field_backup);
}

