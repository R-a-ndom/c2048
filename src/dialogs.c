/*

C  2 0 4 8  console puzzle game

dialogs.c

game menu and dialog windows functions

*/

#include <ncurses.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
#include "c2048.h"
#include "all_draws.h"
#include "dialogs.h"

static const scr_point win_game_menu_msg_start = {2, 10};

const menu_item_data game_menu_data[] = {
  { " NEW GAME ", "Begin a NEW GAME"},
  { "   ABOUT  ", "Show ABOUT window"},
  { "   EXIT   ", "EXIT to shell"}
};


void draw_win_menu_static_elements(WINDOW* win_game_menu)
{
  wdraw_frame(win_game_menu,
              win_game_menu_height, win_game_menu_width,
              zero_point, show_frame);

}

/* --- +++ --- */

program_state game_menu(WINDOW *win_field,
                        game_scr_coords *coords)
{
  WINDOW *win_game_menu;
  win_game_menu = newwin(win_game_menu_height, win_game_menu_width,
                         coords->left_top_game_menu.row,
                         coords->left_top_game_menu.col);
  draw_win_menu_static_elements(win_game_menu);
  wrefresh(stdscr);
  wrefresh(win_field);
  wrefresh(win_game_menu);
  getch();
  delwin(win_game_menu);
  return state_quit;
}
