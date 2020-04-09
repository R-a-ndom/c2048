/*

C  2 0 4 8  console puzzle game

all_draws.c

screen and windows drawing

*/

#include <ncurses.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "all_draws.h"

/* --- +++ --- */

void init_all_colors()
{
  init_pair(col_standart,      COLOR_BLUE,    COLOR_BLACK);

  init_pair(col_title_frame,   COLOR_YELLOW,  COLOR_BLACK);
  init_pair(col_title_picture, COLOR_GREEN,   COLOR_BLACK);
  init_pair(col_title_msg,     COLOR_WHITE,   COLOR_BLACK);

  init_pair(col_field_frame,   COLOR_CYAN,    COLOR_BLACK);

  init_pair(col_debug_text,    COLOR_WHITE,   COLOR_BLACK);
  init_pair(col_debug_data,    COLOR_GREEN,   COLOR_BLACK);
}

/* --- +++ --- */

void draw_grid(WINDOW* win_game_field)
{
  mvwaddch(win_game_field,0,0,'+');
}

#ifdef DEBUG

void debug_print_scr_size()
{
  scr_point screen_size;

  getmaxyx(stdscr, screen_size.row, screen_size.col);
  attron(COLOR_PAIR(col_debug_text));
  printw("| Size : ");
  attron(COLOR_PAIR(col_debug_data));
  attron(A_BOLD);
  printw("%d ", screen_size.row);
  attron(COLOR_PAIR(col_debug_text));
  attroff(A_BOLD);
  printw("x ");
  attron(COLOR_PAIR(col_debug_data));
  attron(A_BOLD);
  printw("%d ", screen_size.col);
}

void debug_print_title_scr(scr_point title_start)
{
  scr_point scr_size;
  getmaxyx(stdscr, scr_size.row, scr_size.col);
  move(scr_size.row - 1, 1);
  debug_print_scr_size();
  attron(COLOR_PAIR(col_debug_text));
  attroff(A_BOLD);
  printw("| Title : ");
  attron(COLOR_PAIR(col_debug_data));
  attron(A_BOLD);
  printw("%d %d ",
          title_start.row, title_start.col);
  attron(COLOR_PAIR(col_debug_text));
  attroff(A_BOLD);
  printw("|");
}

void debug_print_game_scr(game_scr_coords* coords)
{
  move(coords->screen_size.row - 1, 1);
  debug_print_scr_size();
  attron(COLOR_PAIR(col_debug_text));
  attroff(A_BOLD);
  printw("| Field : ");
  attron(COLOR_PAIR(col_debug_data));
  attron(A_BOLD);
  printw("%d %d ",
          coords->left_top_field.row,
          coords->left_top_field.col);
  attron(COLOR_PAIR(col_debug_text));
  attroff(A_BOLD);
  printw("| Game menu : ");
  attron(COLOR_PAIR(col_debug_data));
  attron(A_BOLD);
  printw("%d %d ",
          coords->left_top_game_menu.row,
          coords->left_top_game_menu.col);
  attron(COLOR_PAIR(col_debug_text));
  attroff(A_BOLD);
  printw("| Dialog : ");
  attron(COLOR_PAIR(col_debug_data));
  attron(A_BOLD);
  printw("%d %d ",
          coords->left_top_dialog.row,
          coords->left_top_dialog.col);
  attron(COLOR_PAIR(col_debug_text));
  attroff(A_BOLD);
  printw(" |");
}
#endif
