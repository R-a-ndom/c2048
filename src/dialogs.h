/*

C  2 0 4 8  console puzzle game

dialogs.h

game menu and dialog windows functions

*/

#ifndef DIALOGS_H
#define DIALOGS_H

typedef enum menu_item_state {
  item_unsel,
  item_sel,
} menu_item_state;

enum {
  max_game_menu_pos = 2,
  max_item_msg = 20,
  max_hint_line_msg = 50,

  menu_item_height =  3,
  menu_item_width  = 12,
  menu_items_gap = 15,

};

typedef struct menu_item_data {
  char item_msg[max_item_msg];
  char hint_line_msg[max_hint_line_msg];
  program_state state;
} menu_item_data;


extern const menu_item_data game_menu_data[];

program_state game_menu(WINDOW *win_field,
                        game_scr_coords *coords,
                        const menu_item_data menu_data[]);

#endif
