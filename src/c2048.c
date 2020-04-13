/*

C  2 0 4 8  console puzzle game

c2048.c

base game data types and functions

*/

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "all_draws.h"
#include "dialogs.h"
#include "c2048.h"

/* --- +++ --- */

void game_init()
{
  initscr();
  crmode();
  noecho();
  if ( !has_colors() )
  {
    fprintf(stderr, "C2048 -> Terminal cannot do colors!\n");
    fprintf(stderr, "Colors support required.\n");
    exit(1);
  }
  if ( start_color() != OK )
  {
    fprintf(stderr, "C2048 -> Unable to start colors!\n");
    fprintf(stderr, "Colors support required.\n");
    exit(2);
  }
  init_all_colors();
}

/* --- +++ --- */

game_scr_coords get_game_scr_coords()
{
  game_scr_coords tmp;
  scr_point scr_mid;

  getmaxyx(stdscr, tmp.screen_size.row, tmp.screen_size.col);

  scr_mid = get_middle();

  tmp.left_top_field.row = scr_mid.row - ( win_field_height / 2 );
  tmp.left_top_field.col = scr_mid.col - ( win_field_width / 2 );

  tmp.left_top_game_menu.row = scr_mid.row - ( win_game_menu_height / 2 );
  tmp.left_top_game_menu.col = scr_mid.col - ( win_game_menu_width / 2 );

  tmp.left_top_dialog.row = scr_mid.row - ( win_dialog_height / 2 );
  tmp.left_top_dialog.col = scr_mid.col - ( win_dialog_width / 2 );

  return tmp;
}

/* --- +++ --- */

void game_play()
{
  game_scr_coords scr_coords;
  WINDOW* win_field;
  int current_score, high_score;
  chtype sym;

  current_score = high_score = 0;
  program_state state = state_continue;

  scr_coords = get_game_scr_coords();

  clear();
#ifdef DEBUG
  debug_print_game_scr(&scr_coords);
#endif
  win_field = newwin(win_field_height, win_field_width,
                          scr_coords.left_top_field.row,
                          scr_coords.left_top_field.col);
  draw_field_win_static_elements(win_field);
  wrefresh(stdscr);
  wrefresh(win_field);
  keypad(win_field, TRUE);
  do {
    sym = getch();

    if (sym == local_esc_key)
    {
      state = game_menu(win_field, &scr_coords);
    }

  } while ( state != state_quit );
}