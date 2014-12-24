#include "interface.h"

using namespace std;

int transform_letter(const string str)
{
	if ((str == "а") || (str == "А"))
		return 0;
	if ((str == "б") || (str == "Б"))
		return 1;
	if ((str == "в") || (str == "В"))
		return 2;
	if ((str == "г") || (str == "Г"))
		return 3;
	if ((str == "д") || (str == "Д"))
		return 4;
	if ((str == "е") || (str == "Е"))
		return 5;
	if ((str == "ж") || (str == "Ж"))
		return 6;
	if ((str == "з") || (str == "З"))
		return 7;
	if ((str == "и") || (str == "И"))
		return 8;
	if ((str == "к") || (str == "К"))
		return 9;
	else
		return -1;
}

// true если есть право на еще один ход, повторный ввод данных
bool player_turn(GameField &field)
{
	int x, y;
	bool ship_flag;
	string letter, numstr;

	goto_xy(1, 24);
	cin >> numstr;
	try {
	y = stoi(numstr);
	if ((y < 1) || (y > 10)) {
		cin.clear();
		return true;
	}
	y--;
	}
	catch (...) {
		cin.clear();
		return true;
	}
	cin >> letter;
	x = transform_letter(letter);
	if (x < 0) {
		cin.clear();
		return true;
	}
	if (field.is_marked(x, y))
		return true;
	ship_flag = field.is_ship(x, y);
	field.mark_cell(x, y);

	return ship_flag;
}

int main()
{
	GameField player, computer;
	bool player_win = false, comp_win = false;

	/*
	draw_field(b, true);
	a.place_ship(2, 2, 2, true);
	a.place_ship(2, 3, 4, false);
	a.place_ship(4, 6, 6, false);
	draw_field(a, false);
	*/
	player.randomize_ships();
	computer.randomize_ships();
	player.mark_cell(3, 0);
	player.mark_cell(2, 0);
	player.mark_cell(7, 1);
	refresh_interface(player, computer);
	
	while (!player_win && !comp_win) {
		do {
			 refresh_interface(player, computer);
		} while (player_turn(computer));
		player_win = player.check_win();
		comp_win = computer.check_win();
	}

	return 0;
}
