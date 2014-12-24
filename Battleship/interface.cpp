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
	vector <vector <Cell> > cells = field.get_cells();
	char c;

	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			/*
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
			*/
			if (is_player) {
				c = cells[i][j].player_char();
				print_square(c, 5 + 2 * i, 2 + 2 * j);
			}
			else {
				c = cells[i][j].computer_char();
				print_square(c, 29 + 2 * i, 2 + 2 * j);
			}
		}
	}
}

void print_ships_cnt(GameField &field, bool is_player)
{
	int shift = 2;
	if (!is_player)
		shift = 10;
	goto_xy(52, shift);
	if (is_player)
		cout << "Корабли игрока:";
	else
		cout << "Корабли компьютера:";
	goto_xy(52, shift + 1);
	cout << "Четырехпалубных корбалей: " << field.get_ships_cnt(4);
	goto_xy(52, shift + 2);
	cout << "Трехпалубных корбалей: " << field.get_ships_cnt(3);
	goto_xy(52, shift + 3);
	cout << "Двухпалубных корбалей: " << field.get_ships_cnt(2);
	goto_xy(52, shift + 4);
	cout << "Однопалубных корбалей: " << field.get_ships_cnt(1);
}

void refresh_interface(GameField &player, GameField &computer)
{
	clr_scr();
	print_int_letters(5, 1);
	print_int_letters(29, 1);
	print_int_numbers(2, 2);
	print_int_numbers(26, 2);
	draw_field(player, true);
	draw_field(computer, false);
	print_ships_cnt(player, true);
	print_ships_cnt(computer, false);
	goto_xy(23, 23);
	cout.flush();
}

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