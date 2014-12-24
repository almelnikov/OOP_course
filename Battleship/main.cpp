#include "interface.h"

int main()
{
	clr_scr();
	GameField a, b;

	/*
	draw_field(b, true);
	a.place_ship(2, 2, 2, true);
	a.place_ship(2, 3, 4, false);
	a.place_ship(4, 6, 6, false);
	draw_field(a, false);
	*/
	a.randomize_ships();
	b.randomize_ships();
	a.mark_cell(3, 0);
	a.mark_cell(2, 0);
	a.mark_cell(7, 1);
	refresh_interface(a, b);
	return 0;
}
