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
  state_quit,
  state_new_game,
  state_cancel_move,
  state_show_about,
  state_continue,
  state_continue_and_redraw,
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

  col_field_standard,
  col_field_score_text,
  col_field_hiscore_text,

  col_menu_standard,
  col_menu_text,
  col_menu_sel_frame,

  col_about_standard,
  col_about_button,

  col_debug_text,
  col_debug_data,
};

/* game elements sizes */

enum {
  field_size = 3,
  max_cell_num = 4,

  cell_h_size = 3,
  cell_v_size = 6,

  win_field_height = 22,
  win_field_width  = 31,

  win_game_menu_height =  8,
  win_game_menu_width  = 50,

  win_dialog_height = 10,
  win_dialog_width  = 35,

  win_about_height = 18,
  win_about_width  = 40,

};

enum {
  move_occured,
  move_not_occured
};

/* gameplay elements coords structure */

typedef struct game_scr_coords {
  scr_point screen_size;
  scr_point left_top_field;
  scr_point left_top_game_menu;
  scr_point left_top_dialog;
  scr_point left_top_about;
} game_scr_coords;

/* game score structure */

typedef struct game_score {
  int current;
  int high;
} game_score;

/* game field data types */

typedef struct field_cell
{
  int value;
  int color;
} field_cell;

typedef field_cell game_field[field_size + 1][field_size + 1];

typedef struct move_state
{
  int occuring;
  int result;
} move_state;

#endif