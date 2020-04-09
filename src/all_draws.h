/*

C  2 0 4 8  console puzzle game

all_draws.h

screen and windows drawing

*/

#ifndef ALL_DRAWS_H
#define ALL_DRAWS_H

enum {
  grid_hmax = 29,
  grid_vmax = 29,
};

/*********************************
 * -*- functions declaration -*- *
 *********************************/

void init_all_colors();


#ifdef DEBUG

void debug_print_scr_size();

void debug_print_title_scr(scr_point title_start);

void debug_print_game_scr(game_scr_coords* coords);

#endif

void draw_field_win_static_elements(WINDOW* win_field);

void draw_grid(WINDOW* win_game_field);

#endif