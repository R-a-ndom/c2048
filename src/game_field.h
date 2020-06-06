/*

C  2 0 4 8  console puzzle game

game_field.h

game field functions

*/


#ifndef GAME_FIELD_H
#define GAME_FIELD_H

void init_game_field(game_field field);

void draw_game_field(WINDOW *win_field, game_field field);

void add_new_cell(game_field field);

void copy_field(game_field field_from, game_field field_to);

int there_are_free_cells(game_field field);

int no_moves(game_field field);

#endif