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

static void print_square(char c, int x, int y)
{
	goto_xy(x, y);
	cout << c << c;
	goto_xy(x, y + 1);
	cout << c << c;
}

static void print_int_letters(int x, int y)
{
	goto_xy(x, y);
	cout << "А Б В Г Д Е Ж З И К";
}

static void print_int_numbers(int x, int y)
{
	for (int i = 0; i < 9; i++) {
		goto_xy(x, y + i * 2);
		cout << " " << i + 1;
	}
	goto_xy(x, y + 18);
	cout << "10";
}

static void draw_field(GameField &field, bool is_player)
{
	vector <vector <Cell> > cells = field.get_cells();
	char c;

	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
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

static void print_ships_cnt(GameField &field, bool is_player)
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
	goto_xy(1, 24);
	cout.flush();
}
