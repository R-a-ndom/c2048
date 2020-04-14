/*

C  2 0 4 8  console puzzle game

dialogs.h

game menu and dialog windows functions

*/

#ifndef DIALOGS_H
#define DIALOGS_H

enum {
  max_game_menu_item = 3,
  max_item_msg = 20,
  max_hint_line_msg = 50,
};

typedef struct menu_item_data {
  char item_msg[max_item_msg];
  char hint_line_msg[max_hint_line_msg];
} menu_item_data;


program_state game_menu(WINDOW *win_field,
                        game_scr_coords *coords);

#endif
