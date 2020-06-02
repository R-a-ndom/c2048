/*

C  2 0 4 8  console puzzle game

shift.h

game field shift functions

*/

#ifndef SHIFT_H
#define SHIFT_H

void shift_field_right(game_field field, move_state state);

void shift_field_left(game_field field, move_state state);

void shift_field_up(game_field field, move_state state);

void shift_field_dawn(game_field field, move_state state);


#endif