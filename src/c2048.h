/*

C  2 0 4 8  console puzzle game

c2048.h

base game data types and functions

*/

#ifndef C2048_H
#define C2048_H

enum {
  local_esc_key   =   27,
  local_enter_key = '\n',  // in WINDOWS / DOS    enter key = 13
};                         // in UNIX    / Linux  enter key = 10

#ifdef DEBUG
enum {
  debug_mini_time = 500,
};
#endif

typedef enum program_state {
  state_exit     =  0,
  state_begin    =  1,
  state_continue = 10,
} program_state;

enum {
  cell_hsize = 6,
  cell_vsize = 3,
  win_field_height = 20,
  win_field_width  = 29,
  win_game_menu_height =  8,
  win_game_menu_width  = 40,
  win_game_dialog_height = 15,
  win_game_dialog_width  = 35,
};

typedef struct game_screen_coords {
  scr_point left_top_field;
  scr_point left_top_game_menu;
  scr_point left_top_dialog;
} game_screen_coords;

program_state game_play();

#endif