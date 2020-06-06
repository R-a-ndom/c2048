/*

C  2 0 4 8  console puzzle game

shift.h

game field shift functions

*/

#ifndef SHIFT_H
#define SHIFT_H

void shift_field_left(WINDOW* win_field,
                      game_field field,
                      move_state state);

void shift_field_right(WINDOW* win_field,
                       game_field field,
                       move_state state);

void shift_field_up(WINDOW* win_field,
                    game_field field,
                    move_state state);

void shift_field_dawn(WINDOW* win_field,
                      game_field field,
                      move_state state);

void game_move(WINDOW* win_field,
               chtype sym,
               game_field field,
               game_field field_backup,
               move_state m_state);


#endif