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

static const char main_hint_line[] =
"ARROW KEYS - shift game field | BACKSPACE - cancel last move | ESC - game menu";

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
  tmp.screen_size.row--;
  tmp.screen_size.col--;

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

void draw_game_screen(WINDOW* win_field,
                      game_scr_coords* coords,
                      game_score score)
{
#ifdef DEBUG
  debug_print_game_scr(coords);
#endif
  draw_hint_line(coords, main_hint_line);
  draw_field_win_static_elements(win_field);
  draw_game_score(win_field, score);
  wrefresh(stdscr);
  wrefresh(win_field);
}

/* --- +++ --- */

void update_game_screen(WINDOW* win_field,
                        game_scr_coords* coords,
                        game_score score )
{
#ifdef DEBUG
  debug_print_game_scr(coords);
#endif
  mvwin(win_field,
        coords->left_top_field.row,
        coords->left_top_field.col);
  draw_hint_line(coords, main_hint_line);
  wrefresh(stdscr);
  wrefresh(win_field);
}

/* --- +++ --- */

void game_play()
{
  game_scr_coords coords;
  WINDOW* win_field;
  game_score score;
  chtype sym;

  score.current = score.high = 0;
  program_state state = state_continue;

  coords = get_game_scr_coords();

  clear();
  win_field = newwin(win_field_height, win_field_width,
                     coords.left_top_field.row,
                     coords.left_top_field.col);
  draw_game_screen(win_field, &coords, score);
  keypad(win_field, TRUE);
  do {
    sym = wgetch(win_field);

    switch (sym)
    {
      case KEY_RESIZE:
      {
        clear();
        coords = get_game_scr_coords();
        update_game_screen(win_field, &coords, score);
        state = state_continue;
        break;
      }

      case local_esc_key:
      {
        state = game_menu(win_field, &coords, game_menu_data);
        break;
      }

      default:
      {
        state = state_continue;
      }
    }  /* switch */

    if (state == state_continue_and_redraw)
    {
      erase();
      update_game_screen(win_field, &coords, score);
    }
  } while ( state != state_quit );
}