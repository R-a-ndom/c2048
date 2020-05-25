/*

 NCURS_ETC.H - functions for NCURSES

*/
#define F_CKING_CODE

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

#ifdef F_CKING_CODE

// color structure for using in NCURSES color functions

enum {
  bold_off, // A_BOLD attribute on
  bold_on,  // A_BOLD attribute off
};

typedef struct color_pair_info {
  int number;             // pair number for NCURSES initialization
  int fgc;                // foreground color
  int bgc;                // background color
  int bold_switch;        // bold_on / bold_off
} color_pair_info;

#endif

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
                  int h_size, int v_size,
                  scr_point start_pt,
                  frame_char_set set);

/* drawing an array of strings ,last string must be NULL pointer */

void wadd_string_arr(WINDOW *win_ptr, scr_point start_p, const char **arr);

/* clearing rectangle om *win_ptr window */

void wclear_rect(WINDOW *win_ptr,
                 scr_point start_point,
                 int v_size,int h_size);

#ifdef F_CKING_CODE

/*
 *  turning on the color pair with or without A_BOLD attribute
 *  COLOR_BASE[] is array of COLOR_PAIR_INFO
 */

void turn_on_color_pair(int pair_num,
                        const color_pair_info color_base[],
                        int color_quantity);
#endif

/* pseudo-functions */

#define get_middle()                 get_wmiddle(stdscr)
#define draw_frame( v,h,start,set )  wdraw_frame( stdscr,(v),(h),(start),(set) )
#define add_string_arr( p,arr )      wadd_string_arr( stdscr,(p),(arr) )
#define clear_rect(start_pt,v_s,h_s) wclear_rect( stdscr,(start_pt),(v_s),(h_s) )

#endif