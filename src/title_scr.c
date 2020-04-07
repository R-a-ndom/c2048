/*

C  2 0 4 8 - console puzzle game

title_scr.c

title screen unit

*/

#include <ncurses.h>
#include <unistd.h>

#include "ncurs_etc.h"
#include "c2048.h"
#include "all_draws.h"
#include "title_scr.h"

static const char *title_of_game[] = {
" ><><><><   ><><><><       ><><   ><><><>< ",
"><      >< ><      ><     >< ><  ><      ><",
"       ><  ><      ><    ><  ><  ><      ><",
"     ><    ><      ><   ><   ><   ><><><>< ",
"   ><      ><      ><  ><    ><  ><      ><",
" ><        ><      >< ><><><><>< ><      ><",
"><         ><      ><        ><  ><      ><",
"><><><><><  ><><><><         ><   ><><><>< ",
NULL };

static const scr_point title_start = {2 , 4};
static const scr_point msg_start   = {12, 9};
static const char title_msg[] = "< Press any key to begin game... >";


scr_point get_title_win_start()
{
  scr_point tmp_pos;

  tmp_pos = get_middle();
  tmp_pos.row -= ( title_win_height / 2 );
  tmp_pos.col -= ( title_win_width  / 2 );
  return tmp_pos;
}


void draw_title_screen(WINDOW* win_game_title, scr_point title_pos)
{
  wattron(win_game_title, COLOR_PAIR(col_title_frame));
  wdraw_frame(win_game_title,
              title_win_height, title_win_width,
              zero_point, show_frame);
  wattron(win_game_title, COLOR_PAIR(col_title_picture));
  wadd_string_arr(win_game_title,
                  title_start,
                  title_of_game);
  wattron(win_game_title, COLOR_PAIR(col_title_msg));
  mvwprintw(win_game_title,
            msg_start.row, msg_start.col,
            "%s",title_msg);
}

program_state game_title_screen()
{
  scr_point title_pos;
  WINDOW* win_game_title;
  chtype sym;
  program_state tmp_state = state_continue;

  title_pos = get_title_win_start();
#ifdef DEBUG
  debug_title_scr_print(title_pos);
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
      debug_title_scr_print(title_pos);
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
