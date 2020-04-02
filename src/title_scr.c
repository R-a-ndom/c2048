/*

C  2 0 4 8 - console puzzle game

title_scr.c

title screen unit

*/

#include <ncurses.h>
#include <unistd.h>

#include "ncurs_etc.h"
#include "c2048.h"
#include "title_scr.h"

scr_point get_title_win_start()
{
  scr_point tmp_pos;

  tmp_pos = get_middle();
  tmp_pos.row -= ( title_win_height / 2 );
  tmp_pos.col -= ( title_win_width  / 2 );
  return tmp_pos;
}

#ifdef DEBUG
void debug_point_print(scr_point title_start)
{
  scr_point screen_size;
  getmaxyx(stdscr, screen_size.row, screen_size.col);
  move(screen_size.row - 1, 1);
  printw("| Size : rows %d cols %d",
           screen_size.row, screen_size.col);
  printw(" | Title : row %d col %d |",
           title_start.row, title_start.col);
}
#endif

void draw_title_screen(WINDOW* win_game_title,scr_point title_pos)
{
  wdraw_frame(win_game_title,
              title_win_height, title_win_width,
              zero_point, show_frame);
  mvwprintw(win_game_title,1,1,"%s","C-2048 game");
}

program_state game_title_screen()
{
  scr_point title_pos;
  WINDOW* win_game_title;
  chtype sym;
  program_state tmp_state = state_continue;

  title_pos = get_title_win_start();
#ifdef DEBUG
  debug_point_print(title_pos);
#endif
  win_game_title = newwin(title_win_height, title_win_width,
                          title_pos.row,    title_pos.col);

  draw_title_screen(win_game_title, title_pos);
  wrefresh(stdscr);
  wrefresh(win_game_title);
  keypad(win_game_title,TRUE);
  do {
    sym = wgetch(win_game_title);
    if ( sym == KEY_RESIZE )
    {
      clear();
      title_pos = get_title_win_start();
#ifdef DEBUG
      debug_point_print(title_pos);
#endif
      mvwin(win_game_title, title_pos.row, title_pos.col);
      wrefresh(stdscr);
      wrefresh(win_game_title);
    }
    else if ( sym == local_esc_key )
    {
      tmp_state = state_exit;
    }
    else
    {
      tmp_state = state_begin;
    }
  } while ( tmp_state == state_continue );
  delwin(win_game_title);
  return tmp_state;
}
