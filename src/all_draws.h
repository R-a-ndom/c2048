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

extern const char hint_main[];
extern const char hint_about[];
extern const char hint_game_menu[];

/*********************************
 * -*- functions declaration -*- *
 *********************************/

void init_all_colors();


#ifdef DEBUG

void debug_print_scr_size();

void debug_print_title_scr(scr_point title_start);

void debug_print_game_scr(game_scr_coords* coords);

#endif

void draw_hint_line(game_scr_coords* coords, const char line[]);

void draw_field_win_static_elements(WINDOW* win_field);

void draw_game_score(WINDOW* win_field, game_score score);

void draw_grid(WINDOW* win_game_field);

#endif