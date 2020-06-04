/*

C  2 0 4 8  console puzzle game

shift.c

game field shift functions

*/

#include <ncurses.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "shift.h"

void shift_field_left(game_field field, move_state state)
{

}

void shift_field_right(game_field field, move_state state)
{

}

void shift_field_up(game_field field, move_state state)
{

}

void shift_field_down(game_field field, move_state state)
{

}

void game_move(chtype sym, game_field field, game_field field_backup, move_state m_state)
{
  switch (sym)
  {
    case KEY_LEFT:
    {
      shift_field_left(field, m_state);
      break;
    }

    case KEY_RIGHT:
    {
      shift_field_right(field, m_state);
      break;
    }

    case KEY_UP:
    {
      shift_field_up(field, m_state);
      break;
    }

    case KEY_DOWN:
    {
      shift_field_down(field, m_state);
      break;
    }

  }
}

