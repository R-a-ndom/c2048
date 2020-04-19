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

static const scr_point game_menu_msg   = { 1, 12 };
static const scr_point game_menu_start = { 3,  3 };

const menu_item_data game_menu_data[] = {
  { " NEW GAME ", "Begin a NEW GAME",  state_restart },
  { "   ABOUT  ", "Show ABOUT window", state_show_about },
  { "   EXIT   ", "EXIT to shell",     state_quit }
};


void draw_win_menu_static_elements(WINDOW* win_game_menu)
{
  wdraw_frame(win_game_menu,
              win_game_menu_height, win_game_menu_width,
              zero_point, show_frame);

  mvwprintw(win_game_menu,
            game_menu_msg.row, game_menu_msg.col,
            "C  2 0 4 8  - game menu ");
}


/* --- +++ --- */

void draw_menu_item(WINDOW* win_menu,
                    scr_point item_start,
                    menu_item_data item,
                    menu_item_state item_state)
{
  if ( item_state == item_sel )
  {
    wattrset(win_menu, COLOR_PAIR(col_menu_sel_frame));
    wdraw_frame(win_menu,
                menu_item_height, menu_item_width,
                item_start, star_frame );
  } else {
    wdraw_frame(win_menu,
                menu_item_height, menu_item_width,
                item_start, hide_frame );
  }

  wattrset(win_menu, COLOR_PAIR(col_menu_text));
  wmove(win_menu, item_start.row + 1, item_start.col + 1);
  wprintw(win_menu, "%s", item.item_msg);
}

/* --- +++ --- */

void draw_full_menu(WINDOW* win_menu,
                    int select_pos,
                    const menu_item_data menu_data[] )
{
  int current_pos = 0;
  scr_point draw_pos = game_menu_start;

  wattrset(win_menu, COLOR_PAIR(col_menu_text));
  while(current_pos < select_pos)
  {
     draw_menu_item(win_menu,
                    draw_pos,
                    menu_data[current_pos],
                    item_unsel);
    current_pos++;
    draw_pos.col += menu_items_gap;
  }

  draw_menu_item(win_menu,
                 draw_pos,
                 menu_data[current_pos],
                 item_sel);
  current_pos++;
  draw_pos.col += menu_items_gap;

  wattrset(win_menu, COLOR_PAIR(col_menu_text));
  while(current_pos <= max_game_menu_pos)
  {
     draw_menu_item(win_menu,
                    draw_pos,
                    menu_data[current_pos],
                    item_unsel);
    current_pos++;
    draw_pos.col += menu_items_gap;
  }

}

/* --- +++ --- */

program_state game_menu(WINDOW *win_field,
                        game_scr_coords *coords)
{
  WINDOW *win_menu;
  int menu_current_pos = 0;

  win_menu = newwin(win_game_menu_height, win_game_menu_width,
                         coords->left_top_game_menu.row,
                         coords->left_top_game_menu.col);
  wattrset(win_menu, COLOR_PAIR(col_menu_standard));
  draw_win_menu_static_elements(win_menu);
  draw_full_menu(win_menu, menu_current_pos, game_menu_data);
#ifdef DEBUG
  mvwprintw(win_menu, 1, 1, "%d", menu_current_pos);
#endif
  wrefresh(stdscr);
  wrefresh(win_field);
  wrefresh(win_menu);
  getch();
  delwin(win_menu);
  return state_quit;
}
