/*

C  2 0 4 8  console puzzle game

all_draws.h

screen and windows drawing

*/

#ifndef ALL_DRAWS_H
#define ALL_DRAWS_H



/*********************************
 * -*- functions declaration -*- *
 *********************************/

void init_all_colors();

void draw_grid(WINDOW* win_game_field);

#ifdef DEBUG

void debug_print_scr_size();

void debug_print_title_scr(scr_point title_start);

void debug_print_game_scr(game_scr_coords* coords);

#endif

#endif