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

const field_cell clear_cell = { 0, 0, BOOL_FALSE };

/* cell manipulation functions */

/* --- +++ --- */

void swap_cells(field_cell* cell_from, field_cell* cell_to)
{
  field_cell cell_tmp;
  cell_tmp = *cell_to;
  *cell_to = *cell_from;
  *cell_from = cell_tmp;
}

/* --- +++ --- */

void reset_update_lock(game_field field)
{
  int i,j;
  for(i = 0; i < field_size; i++)
    for(j = 0; j < field_size; j++)
      field[i][j].update_lock = BOOL_FALSE;
}

/* --- +++ --- */

void update_cell(game_field field,
                 int row_pos, int col_pos,
                 move_state* m_state)
{
  field[row_pos][col_pos].value *= 2;
  field[row_pos][col_pos].color += 1;
  m_state->score += field[row_pos][col_pos].value;
  if (m_state->move_occuring == BOOL_FALSE)
  {
    m_state->move_occuring = BOOL_TRUE;
  }
  field[row_pos][col_pos].update_lock = BOOL_TRUE;
}

/* pushing cells */

void push_cell_left(game_field field, int row_pos, int col_pos, move_state* m_state)
{
  while(field[row_pos][col_pos-1].value == 0)
  {
    if (col_pos == 0)
    {
      break;
    } else {
      swap_cells(&field[row_pos][col_pos-1], &field[row_pos][col_pos]);
      col_pos--;
    }
  }
  if ( col_pos != 0 )
  {
    if ( (field[row_pos][col_pos-1].value == field[row_pos][col_pos].value)
        && (!field[row_pos][col_pos].update_lock) )
    {
      update_cell(field, row_pos, col_pos-1, m_state);
      field[row_pos][col_pos] = clear_cell;
    }
  }
}

/* --- +++ --- */

void push_cell_right(game_field field, int row_pos, int col_pos)
{
  while(field[row_pos][col_pos+1].value == 0)
  {
    if (col_pos == field_size)
    {
      break;
    } else {
      swap_cells(&field[row_pos][col_pos+1], &field[row_pos][col_pos]);
      col_pos++;
    }
  }
}

/* --- +++ --- */

void push_cell_up(game_field field, int row_pos, int col_pos)
{
  while(field[row_pos-1][col_pos].value == 0)
  {
    if (row_pos == 0)
    {
      break;
    } else {
      swap_cells(&field[row_pos-1][col_pos], &field[row_pos][col_pos]);
      row_pos--;
    }
  }
}

/* --- +++ --- */

void push_cell_down(game_field field, int row_pos, int col_pos)
{
  while(field[row_pos+1][col_pos].value == 0)
  {
    if (row_pos == field_size)
    {
      break;
    } else {
      swap_cells(&field[row_pos+1][col_pos], &field[row_pos][col_pos]);
      row_pos++;
    }
  }
}

/* shifting functions */

void shift_field_left(WINDOW* win_field,
                      game_field field,
                      move_state* m_state)
{
  int row_pos, col_pos;

  for(col_pos = 0; col_pos <= field_size-1; col_pos++)
  {
    for(row_pos = 0; row_pos <= field_size; row_pos++)
    {
      if(field[row_pos][col_pos].value == 0)
      {
        if (field[row_pos][col_pos+1].value != 0)
        {
          push_cell_left(field, row_pos, col_pos+1, m_state);
        }
      } else {
        if((field[row_pos][col_pos].value == field[row_pos][col_pos+1].value) &&
           (!field[row_pos][col_pos].update_lock))
        {
          update_cell(field, row_pos, col_pos, m_state);
          field[row_pos][col_pos+1] = clear_cell;
        }
      }
    }
    draw_game_field(win_field, field);
    wrefresh(win_field);
    napms(draw_pause);
  }
}

/* --- +++ --- */

void shift_field_right(WINDOW* win_field,
                       game_field field,
                       move_state* m_state)
{
  int row_pos, col_pos;

  for(col_pos = field_size; col_pos >= 1; col_pos--)
  {
    for(row_pos = 0; row_pos <= field_size; row_pos++)
    {
      if(field[row_pos][col_pos].value == 0)
      {
        if (field[row_pos][col_pos-1].value != 0)
        {
          push_cell_right(field, row_pos, col_pos-1);
        }
      } else {
        if((field[row_pos][col_pos].value == field[row_pos][col_pos-1].value) &&
           (!field[row_pos][col_pos].update_lock))
        {
          update_cell(field, row_pos, col_pos, m_state);
          field[row_pos][col_pos-1] = clear_cell;
        }
      }
    }
    draw_game_field(win_field, field);
    wrefresh(win_field);
    napms(draw_pause);
  }
}

/* --- +++ --- */

void shift_field_up(WINDOW* win_field,
                    game_field field,
                    move_state* m_state)
{
  int row_pos, col_pos;

  for(row_pos = 0; row_pos <= field_size-1; row_pos++)
  {
    for(col_pos = 0; col_pos <= field_size; col_pos++)
    {
      if(field[row_pos][col_pos].value == 0)
      {
        if (field[row_pos+1][col_pos].value != 0)
        {
          push_cell_up(field, row_pos+1, col_pos);
        }
      } else {
        if((field[row_pos][col_pos].value == field[row_pos+1][col_pos].value) &&
           (!field[row_pos][col_pos].update_lock))
        {
          update_cell(field, row_pos, col_pos, m_state);
          field[row_pos+1][col_pos] = clear_cell;
        }
      }
    }
    draw_game_field(win_field, field);
    wrefresh(win_field);
    napms(draw_pause);
  }
}

/* --- +++ --- */

void shift_field_down(WINDOW* win_field,
                      game_field field,
                      move_state* m_state)
{
  int row_pos, col_pos;

  for(row_pos = field_size; row_pos >= 1; row_pos--)
  {
    for(col_pos = 0; col_pos <= field_size; col_pos++)
    {
      if(field[row_pos][col_pos].value == 0)
      {
        if (field[row_pos-1][col_pos].value != 0)
        {
          push_cell_down(field, row_pos-1, col_pos);
        }
      } else {
        if((field[row_pos][col_pos].value == field[row_pos-1][col_pos].value) &&
           (!field[row_pos][col_pos].update_lock))
        {
          update_cell(field, row_pos, col_pos, m_state);
          field[row_pos-1][col_pos] = clear_cell;
        }
      }
    }
    draw_game_field(win_field, field);
    wrefresh(win_field);
    napms(draw_pause);
  }
}

/* game move function */

void game_move(WINDOW* win_field,
               chtype sym,
               game_field field,
               game_field field_backup,
               move_state* m_state)
{
  m_state->move_occuring = BOOL_FALSE;
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
  if (m_state->move_occuring)
  copy_field(field, field_backup);
}

