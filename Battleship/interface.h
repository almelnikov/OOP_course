#ifndef _INTERFACE_HEADER
#define _INTERFACE_HEADER

#include <iostream>
#include "game_logic.h"

void clr_scr();
void goto_xy(int x, int y);
void refresh_interface(GameField &player, GameField &computer);

#endif

