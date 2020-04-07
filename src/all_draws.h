/*

C  2 0 4 8  console puzzle game

all_draws.h

screen and windows drawing

*/

#ifndef ALL_DRAWS_H
#define ALL_DRAWS_H

enum {
  other_color_count = 6,
};

enum {
  col_standart = 20,

  col_title_frame,
  col_title_picture,
  col_title_msg,

  col_field_frame,

  col_debug_text,
  col_debug_data,
};

extern const color_pair_info colors_base_other[];

/*********************************
 * -*- functions declaration -*- *
 *********************************/

void init_all_colors();

void draw_grid(WINDOW* win_game_field);

#ifdef DEBUG

void debug_title_scr_print(scr_point title_start);

#endif

#endif