/*

C  2 0 4 8 - console puzzle game

title_scr.c

title screen unit

*/

#include <ncurses.h>
#include <unistd.h>

#include "ncurs_etc.h"
#include "c2048_base.h"
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


scr_point get_left_top_title_win()
{
  scr_point tmp_pos;

  tmp_pos = get_middle();
  tmp_pos.row -= ( win_title_height / 2 );
  tmp_pos.col -= ( win_title_width  / 2 );
  return tmp_pos;
}


void draw_title_screen(WINDOW* win_game_title, scr_point title_pos)
{
  wattron(win_game_title, COLOR_PAIR(col_title_frame));
  wdraw_frame(win_game_title,
              win_title_height, win_title_width,
              zero_point, show_frame);
  wattron(win_game_title, COLOR_PAIR(col_title_picture) | A_BOLD );
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

  title_pos = get_left_top_title_win();
#ifdef DEBUG
  debug_print_title_scr(title_pos);
#endif
  win_game_title = newwin(win_title_height, win_title_width,
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
      title_pos = get_left_top_title_win();
#ifdef DEBUG
      debug_print_title_scr(title_pos);
#endif
      mvwin(win_game_title, title_pos.row, title_pos.col);
      wrefresh(stdscr);
      wrefresh(win_game_title);
    }
    else if ( sym == local_esc_key )
    {
      tmp_state = state_quit;
    }
    else
    {
      tmp_state = state_new_game;
    }
  } while ( tmp_state == state_continue );
  delwin(win_game_title);
  return tmp_state;
}
