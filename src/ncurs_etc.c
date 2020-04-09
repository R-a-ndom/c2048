/*

 NCURS_ETC.C - other functions for NCURSES


 */

#define F_CKING_CODE

#include <unistd.h>
#include <ncurses.h>

#include "ncurs_etc.h"


const scr_point zero_point = {0,0};

const frame_char_set show_frame = { '+', '-', '|' };
const frame_char_set hide_frame = { ' ', ' ', ' ' };
const frame_char_set star_frame = { '*', '*', '*' };


scr_point get_wmiddle(WINDOW *win_ptr)
{
  scr_point tmp;
  getmaxyx(win_ptr,tmp.row,tmp.col);
  tmp.row /= 2;
  tmp.col /= 2;
  return tmp;
}

/*
   LeftTop  --  TopHorizontal  --  RightTop
      |                                |
   LeftVertical                    RightVertical
      |                                |
   LeftBottom - BottomHorizontal - RightBottom
*/


void wdraw_frame (WINDOW *win_ptr,
                  int v_size,int h_size,
                  scr_point start_pt,
                  frame_char_set set)
{
  int i;
  h_size--;
  v_size--;

  mvwaddch                 // Left Top corner
    (win_ptr,
     start_pt.row,
     start_pt.col,
     set.corner);
  mvwaddch                 // Right Top corner
    (win_ptr,
     start_pt.row,
     start_pt.col + h_size,
     set.corner);
  mvwaddch                 // Left Bottom corner
    (win_ptr,
     start_pt.row + v_size,
     start_pt.col,
     set.corner);
  mvwaddch                 // Right Bottom corner
    (win_ptr,
     start_pt.row + v_size,
     start_pt.col + h_size,
     set.corner);

  for(i=start_pt.col + 1; i < start_pt.col + h_size; i++)
  {
    mvwaddch(win_ptr,                  // Top Horizontal line
             start_pt.row, i,
             set.h_line);
    mvwaddch(win_ptr,                  // Bottom Horizontal line
             start_pt.row + v_size, i,
             set.h_line);
  }

  for(i=start_pt.row + 1; i < start_pt.row + v_size; i++)
  {
    mvwaddch(win_ptr,                 // Left Vertical line
             i, start_pt.col,
             set.v_line);
    mvwaddch(win_ptr,                 // Right Vertical line
             i, start_pt.col + h_size,
             set.v_line);
  }

  return;
}

/* *** *** *** */

void wadd_string_arr(WINDOW *win_ptr,scr_point start_p, const char **arr)
{
  int i = 0;
  while(arr[i] != NULL)
  {
    mvwprintw(win_ptr,start_p.row+i,start_p.col,"%s",arr[i]);
    i++;
  }
}

/* *** *** *** */

void wclear_rect(WINDOW *win_ptr,
                 scr_point start_point,
                 int v_size,int h_size)
{
  int i,j;
  for(i = start_point.row; i < (start_point.row + v_size);i++)
  {
    for(j = start_point.col; j < (start_point.col + h_size); j++)
      mvwaddch(win_ptr,i,j,' ');
  }
}

/* *** *** *** */

#ifndef F_CKING_CODE

void init_color_pair(color_pair_info pair)
{
  init_pair(pair.number, pair.fgc, pair.bgc);
}

/* *** *** *** */

void turn_on_color_pair(int pair_num,
                        const color_pair_info color_base[],
                        int color_quantity)
{
  int i;
  for(i = 0; i < color_quantity; i++)
  {
    if ( color_base[i].number == pair_num )
    {
      attrset(COLOR_PAIR(color_base[i].number));
      if ( color_base[i].bold_switch == bold_on )
        attron(A_BOLD);
      else
        attroff(A_BOLD);
      break;
    }
  }
}

#endif