/*

C  2 0 4 8  console puzzle game

c2048.c

base game data types and functions

*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "all_draws.h"
#include "dialogs.h"
#include "c2048.h"
#include "game_field.h"
#include "shift.h"

/* --- +++ --- */

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

void start_new_game(game_field main_field, game_field backup_field)
{
  init_game_field(main_field);
  add_new_cell(main_field);
  add_new_cell(main_field);
  copy_field(main_field, backup_field);
}

/* --- +++ --- */

void draw_game_screen(WINDOW* win_field,
                      game_scr_coords* coords,
                      game_score score)
{
#ifdef DEBUG
  debug_print_game_scr(coords);
#else
  print_head_message(coords);
#endif
  draw_hint_line(coords, hint_main);
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
#else
  print_head_message(coords);
#endif
  mvwin(win_field,
        coords->left_top_field.row,
        coords->left_top_field.col);
  draw_hint_line(coords, hint_main);
  wrefresh(stdscr);
  touchwin(win_field);
  wrefresh(win_field);
}

/* --- +++ --- */

void game_play()
{
  game_scr_coords coords;
  WINDOW* win_field;
  game_score score;
  move_state m_state;
  chtype sym;

  game_field main_field;
  game_field backup_field;

  score.current = score.high = 0;
  program_state state = state_continue;

  srand(time(NULL));
  coords = get_game_scr_coords();
  clear();
  win_field = newwin(win_field_height, win_field_width,
                     coords.left_top_field.row,
                     coords.left_top_field.col);
  draw_game_screen(win_field, &coords, score);
  start_new_game(main_field, backup_field);
  draw_game_field(win_field, main_field);
  keypad(win_field, TRUE);

/****************/
/*  MAIN CYCLE  */
/****************/

  for(;;)
  {
    sym = wgetch(win_field);

    switch (sym)
    {
      case KEY_LEFT: case KEY_RIGHT: case KEY_UP: case KEY_DOWN:
      {
        game_move(win_field, sym, main_field, backup_field, m_state);
        state = state_continue;
        break;
      }

      case KEY_RESIZE:
      {
        state = state_continue_and_redraw;
        break;
      }

      case KEY_F(10):
      {
        state = game_menu(win_field, &coords, game_menu_data);
        break;
      }

      default:
      {
        state = state_continue;
      }
    }  /* switch */

    switch (state)
    {

      case state_new_game:
      {
        erase();
        update_game_screen(win_field, &coords, score);
        break;
      }
      case state_cancel_move:
      {
        erase();
        update_game_screen(win_field, &coords, score);
        break;
      }

      case state_show_about:
      {
        about_window(win_field, &coords);
        erase();
        update_game_screen(win_field, &coords, score);
        state = state_continue;
        break;
      }

      case state_continue:
      {
        erase();
        update_game_screen(win_field, &coords, score);
        break;
      }

      case state_continue_and_redraw:
      {
        erase();
        update_game_screen_after_resizing(&coords,
                                          win_field,
                                          NULL, NULL,
                                          hint_main);
        break;
      }

      case state_quit:
      {
        endwin();
        printf("C2048 : thanks for playing !\n");
        exit(EXIT_SUCCESS);
      }
    }
  }
}