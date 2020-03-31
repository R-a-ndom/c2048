/*

 NCURS_ETC.H - functions for NCURSES

*/

#ifndef NCURS_ETC_H
#define NCURS_ETC_H

// point coordinates on screen / window

typedef struct scr_point
{
  int row,col;
} scr_point;

// symbol set for frame drawing

typedef struct frame_char_set {
  char corner;
  char h_line;
  char v_line;
} frame_char_set;

// color structure for using in NCURSES color functions

typedef struct symbol_color {
  short fg_color;
  short bg_color;
} symbol_color;

// *** *** ***

extern const scr_point zero_point;
extern const frame_char_set show_frame;
extern const frame_char_set hide_frame;
extern const frame_char_set star_frame;

// *** *** ***

/* middle of *win_ptr window */

scr_point get_wmiddle(WINDOW *win_ptr);

/* drawing frame on *win_ptr window */

void wdraw_frame (WINDOW *win_ptr,
                  int h_size,int v_size,
                  scr_point start_pt,
                  frame_char_set set);

/* drawing an array of strings ,last string must be NULL pointer */

void wadd_string_arr(WINDOW *win_ptr,scr_point start_p, const char **arr);

/* clearing rectangle om *win_ptr window */

void wclear_rect(WINDOW *win_ptr,
                 scr_point start_point,
                 int v_size,int h_size);

/* pseudo-functions */

#define get_middle()                 get_wmiddle(stdscr)
#define draw_frame( v,h,start,set )  wdraw_frame( stdscr,(v),(h),(start),(set) )
#define add_string_arr( p,arr )      wadd_string_arr( stdscr,(p),(arr) )
#define clear_rect(start_pt,v_s,h_s) wclear_rect( stdscr,(start_pt),(v_s),(h_s) )

#endif