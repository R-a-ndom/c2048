/*

C  2 0 4 8  console puzzle game

c2048.h

base game data types and functions

*/

#ifndef C2048_H
#define C2048_H

enum {
  local_esc_key   =   27,
  local_enter_key = '\n',  // in WINDOWS / DOS    enter key = 13
};                         // in UNIX    / Linux  enter key = 10


typedef enum program_state {
  state_exit     =  0,
  state_begin    =  1,
  state_continue = 10,
} program_state;

program_state game_play();

#endif