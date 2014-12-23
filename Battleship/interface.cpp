#include <iostream>
#include "game_logic.h"

using namespace std;

static const int field_size = 10;

void clr_scr()
{
	cout << "\E[H\E[2J";
}

void goto_xy(int x, int y)
{
	cout << "\E[" << y << ";" << x << "H";
}

void print_square(char c, int x, int y)
{
	goto_xy(x, y);
	cout << c << c;
	goto_xy(x, y + 1);
	cout << c << c;
}

void print_int_letters(int x, int y)
{
	goto_xy(x, y);
	cout << "А Б В Г Д Е Ж З И К";
}

void print_int_numbers(int x, int y)
{
	for (int i = 0; i < 9; i++) {
		goto_xy(x, y + i * 2);
		cout << " " << i + 1;
	}
	goto_xy(x, y + 18);
	cout << "10";
}

void draw_field(GameField &field, bool is_player)
{
	vector <vector <cell_state> > cells = field.get_cells();
	char c;

	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			switch (cells[i][j]) {
				case CELL_EMPTY:
					c = 'a'; //tmp
					break;

				case CELL_EMPTY_M:
					c = '.';
					break;

				case CELL_SHIP:
					if (is_player)
						c = '0';
					else
						c = ' ';
					break;

				case CELL_SHIP_M:
					c = 'X';
					break;
			}
			if (is_player)
				print_square(c, 5 + 2 * i, 2 + 2 * j);
			else
				print_square(c, 29 + 2 * i, 2 + 2 * j);
		}
	}
}

void refresh_interface()
{
	print_int_letters(5, 1);
	print_int_letters(29, 1);
	print_int_numbers(2, 2);
	print_int_numbers(26, 2);
	cout.flush();
}

int main()
{
	clr_scr();
	refresh_interface();
	GameField a;
	draw_field(a, true);
	a.place_ship(2, 2, 2, true);
	a.place_ship(4, 6, 6, false);
	draw_field(a, false);
	//goto_xy(5, 6);
	//cout.flush();
	//cout << "afdafdaf" << endl;
	//print_square('*', 10, 10);

	return 0;
}