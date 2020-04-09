/*

C  2 0 4 8  console puzzle game

c2048_base.h

base game data types and functions

*/


#ifndef C2048_BASE_H
#define C2048_BASE_H

enum {
  local_esc_key   =   27,
  local_enter_key = '\n',  // in WINDOWS / DOS    enter key = 13
};                         // in UNIX    / Linux  enter key = 10

/* program states */

typedef enum program_state {
  state_quit     =  0,
  state_begin    =  1,
  state_continue = 10,
} program_state;


/* color pairs numbers */

enum {
  other_colors_count = 10,
};

enum {
  col_standard = 20,

  col_title_frame,
  col_title_picture,
  col_title_msg,

  col_field_frame,
  col_field_text,
  col_field_score_text,
  col_field_hiscore_text,

  col_field_standard,
  col_debug_text,
  col_debug_data,
};

/* game elements sizes */

enum {
  side_size = 3,

  cell_hsize = 3,
  cell_vsize = 6,

  win_field_height = 22,
  win_field_width  = 31,

  win_game_menu_height =  6,
  win_game_menu_width  = 40,

  win_dialog_height = 10,
  win_dialog_width  = 35,
};

/* gameplay elements coords structure */

typedef struct game_scr_coords {
  scr_point screen_size;
  scr_point left_top_field;
  scr_point left_top_game_menu;
  scr_point left_top_dialog;
} game_scr_coords;

#endif