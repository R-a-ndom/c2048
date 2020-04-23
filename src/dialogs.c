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

const char win_menu_title[] = "C  2 0 4 8  - game menu ";

const menu_item_data game_menu_data[] = {
  { " NEW GAME ", "Begin a NEW GAME",  state_restart },
  { "   ABOUT  ", "Show ABOUT window", state_show_about },
  { "   EXIT   ", "EXIT to shell",     state_quit }
};


/* --- +++ --- */
/* --- +++ --- */

void draw_win_menu_static_elements(WINDOW* win_game_menu)
{
  wdraw_frame(win_game_menu,
              win_game_menu_height, win_game_menu_width,
              zero_point, show_frame);

  mvwprintw(win_game_menu,
            game_menu_msg.row, game_menu_msg.col,
            win_menu_title);
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

  wattrset(win_menu, COLOR_PAIR(col_menu_text) | A_BOLD );
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

void draw_menu_window(WINDOW* win_menu, game_scr_coords* coords)
{
  int start_menu_pos = 0;
  wbkgd(win_menu, COLOR_PAIR(col_menu_standard));
  draw_win_menu_static_elements(win_menu);
  draw_full_menu(win_menu, start_menu_pos, game_menu_data);
#ifdef DEBUG
  mvwprintw(win_menu, 1, 1, "%d", start_menu_pos);
#endif
  wrefresh(win_menu);
}

/* --- +++ --- */

void update_menu_window(WINDOW* win_menu,
                        int current_menu_pos)
{
  draw_full_menu(win_menu, current_menu_pos, game_menu_data);
#ifdef DEBUG
  mvwprintw(win_menu, 1, 1, "%d", current_menu_pos);
#endif
  wrefresh(win_menu);
}

/* --- +++ --- */

void update_menu_screen(WINDOW* win_field,
                        WINDOW* win_menu,
                        game_scr_coords* coords)
{
  clear();
  *coords = get_game_scr_coords();
  mvwin(win_field,
        coords->left_top_field.row,
        coords->left_top_field.col);
  mvwin(win_menu,
        coords->left_top_game_menu.row,
        coords->left_top_game_menu.col);
#ifdef DEBUG
  debug_print_game_scr(coords);
#endif
  wrefresh(stdscr);
  wrefresh(win_field);
  wrefresh(win_menu);
}

/* --- +++ --- */

program_state game_menu(WINDOW *win_field,
                        game_scr_coords* coords,
                        const menu_item_data menu_data[] )
{
  WINDOW *win_menu;
  int menu_current_pos = 0;
  chtype sym;
  program_state tmp_state = state_continue;

  win_menu = newwin(win_game_menu_height, win_game_menu_width,
                         coords->left_top_game_menu.row,
                         coords->left_top_game_menu.col);
  draw_menu_window(win_menu, coords);
  draw_hint_line(coords, menu_data[menu_current_pos].hint_line_msg);
  keypad(win_menu, TRUE);
  do {
    sym = wgetch(win_menu);

    switch (sym)
    {
      case local_esc_key:
      {
        tmp_state = state_continue_and_redraw;
        break;
      }

      case KEY_LEFT:  // <<<
      {
        if (menu_current_pos > 0)
        {
          menu_current_pos--;
          update_menu_window(win_menu, menu_current_pos);
          draw_hint_line(coords, menu_data[menu_current_pos].hint_line_msg);
        }
        tmp_state = state_continue;
        break;
      }

      case KEY_RIGHT: // >>>
        if (menu_current_pos < max_game_menu_pos)
        {
          menu_current_pos++;
          update_menu_window(win_menu, menu_current_pos);
          draw_hint_line(coords, menu_data[menu_current_pos].hint_line_msg);
        }
        tmp_state = state_continue;
        break;

      case KEY_RESIZE:
      {
        update_menu_screen(win_field, win_menu, coords);
        tmp_state = state_continue;
        break;
      }

      default:
      {
        tmp_state = menu_data[menu_current_pos].state;
        break;
      }
    }  /* switch */
  } while ( tmp_state == state_continue );

  delwin(win_menu);
  return tmp_state;
}
