/*

C  2 0 4 8  console puzzle game

all_draws.c

screen and windows drawing

*/

#include <ncurses.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "all_draws.h"

const char hint_main[] =
"ARROW KEYS - shift game field | BACKSPACE - cancel last move | ESC - game menu";

const char hint_about[] =
"ANY KEY - resume game";

const char hint_game_menu[] =
"LEFT, RIGHT - move cursor | ANY KEY - select | ESC - resume game";

static const char score_msg[] = "SCORE          HIGH SCORE";

const char head_message[] =
"Try to become an 2048 number. GOOD LUCK!";

static const scr_point grid_start    = {  4,  1 };
static const scr_point score_start   = {  2,  1 };
static const scr_point hiscore_start = {  2, 16 };

/* --- +++ --- */

void init_all_colors()
{
/* cell colors */
  init_pair( 1, COLOR_YELLOW, COLOR_BLUE);
  init_pair( 2, COLOR_RED, COLOR_GREEN);
  init_pair( 3, COLOR_WHITE, COLOR_RED);
  init_pair( 4, COLOR_WHITE, COLOR_MAGENTA);
  init_pair( 5, COLOR_GREEN, COLOR_YELLOW);
  init_pair( 6, COLOR_GREEN, COLOR_WHITE);
  init_pair( 7, COLOR_CYAN, COLOR_BLACK);
  init_pair( 8, COLOR_CYAN, COLOR_BLUE);
  init_pair( 9, COLOR_BLACK, COLOR_CYAN);
  init_pair(10, COLOR_WHITE, COLOR_GREEN);
  init_pair(11, COLOR_YELLOW, COLOR_RED);
  init_pair(12, COLOR_BLUE, COLOR_MAGENTA);
  init_pair(13, COLOR_GREEN, COLOR_YELLOW);
  init_pair(14, COLOR_RED, COLOR_WHITE);

  init_pair(col_standard, COLOR_BLUE,    COLOR_BLACK);
/* title picture */
  init_pair(col_title_frame,   COLOR_YELLOW, COLOR_BLACK);
  init_pair(col_title_picture, COLOR_CYAN,   COLOR_MAGENTA);
  init_pair(col_title_msg,     COLOR_WHITE,  COLOR_BLACK);
/* game field */
  init_pair(col_field_standard,     COLOR_WHITE,   COLOR_BLACK);
  init_pair(col_field_score_text,   COLOR_CYAN,    COLOR_BLACK);
  init_pair(col_field_hiscore_text, COLOR_MAGENTA, COLOR_BLACK);
/* game menu */
  init_pair(col_menu_standard,    COLOR_CYAN,    COLOR_BLUE);
  init_pair(col_menu_text,        COLOR_YELLOW,  COLOR_BLUE);
  init_pair(col_menu_sel_frame,   COLOR_MAGENTA, COLOR_BLUE);
/* about window */
  init_pair(col_about_standard, COLOR_WHITE, COLOR_GREEN);
  init_pair(col_about_button,   COLOR_RED,   COLOR_GREEN);
/* debug info */
  init_pair(col_debug_text, COLOR_WHITE, COLOR_BLACK);
  init_pair(col_debug_data, COLOR_GREEN, COLOR_BLACK);
}

/* --- +++ ---
TODO: coordinates calculating in other function
*/

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

  tmp.left_top_about.row = scr_mid.row - ( win_about_height / 2 );
  tmp.left_top_about.col = scr_mid.col - ( win_about_width / 2 );

  return tmp;
}

/* --- +++ --- */

#ifdef DEBUG /*  debug printing */

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
  move( 0, 1);
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
  move( 0, 1);
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
  printw("| Menu : ");
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
  printw("| About : ");
  attron(COLOR_PAIR(col_debug_data));
  attron(A_BOLD);
  printw("%d %d ",
          coords->left_top_about.row,
          coords->left_top_about.col);

  attron(COLOR_PAIR(col_debug_text));
  attroff(A_BOLD);
  printw("|");
}
#else

void print_head_message(game_scr_coords* coords)
{
  int head_msg_h_pos;
  head_msg_h_pos = ( coords->screen_size.col - head_msg_length  ) / 2;
  move(0, head_msg_h_pos);
  printw("%s", head_message);
}

#endif

/* --- +++ --- */

void draw_hint_line(game_scr_coords* coords, const char line[])
{
  int i;
  wmove(stdscr, coords->screen_size.row, 1);
  for(i = 1; i < coords->screen_size.col; i++)
  {
    addch(' ');
  }
  mvwprintw(stdscr, coords->screen_size.row, 1, line);
}

/* --- +++ --- *//* --- +++ --- */

void draw_grid(WINDOW* win_field)
{
  scr_point sym_pos;
  for(sym_pos.row = grid_start.row;
      sym_pos.row <= grid_hmax;
      sym_pos.row += (cell_h_size+1))
  {
    for(sym_pos.col = grid_start.col;
        sym_pos.col <= grid_vmax;
        sym_pos.col += (cell_v_size+1))
      {
         mvwaddch(win_field, sym_pos.row, sym_pos.col, '+');
      }
  }
}

/* --- +++ --- */

void draw_game_score(WINDOW* win_field, game_score score)
{
  wattron(win_field, COLOR_PAIR(col_field_score_text));
  wmove(win_field, score_start.row, score_start.col);
  wprintw(win_field,"%d",score.current);
  wattron(win_field, COLOR_PAIR(col_field_hiscore_text));
  wmove(win_field, hiscore_start.row, hiscore_start.col);
  wprintw(win_field,"%d",score.high);
}

/* --- +++ --- */

void draw_field_win_static_elements(WINDOW* win_field)
{
  int i;

  wattron(win_field, COLOR_PAIR(col_field_standard) | A_NORMAL);
  wdraw_frame(win_field,
              win_field_height, win_field_width,
              zero_point,
              show_frame);
  mvwaddch(win_field, 3, 0, '+');
  for(i=1; i < win_field_width - 1; i++)
  {
     waddch(win_field, '-');
  }
  waddch(win_field, '+');
  draw_grid(win_field);

  wattron(win_field, A_BOLD);
  mvwprintw(win_field, 1, 1, "%s", score_msg);
}

/* --- +++ --- */

void update_game_screen_after_resizing(game_scr_coords *coords,
                                       WINDOW *win_field,
                                       WINDOW *win_another,
                                       scr_point *win_another_coords,
                                       const char *hint_line)

{
  clear();
  *coords = get_game_scr_coords();
  mvwin(win_field,
        coords->left_top_field.row,
        coords->left_top_field.col);
#ifdef DEBUG
  debug_print_game_scr(coords);
#else
  print_head_message(coords);
#endif
  draw_hint_line(coords, hint_line);
  wrefresh(stdscr);
  touchwin(win_field);
  wrefresh(win_field);
  if (win_another)
  {
    mvwin(win_another,
          win_another_coords->row,
          win_another_coords->col);
    touchwin(win_another);
    wrefresh(win_another);
  }
}
