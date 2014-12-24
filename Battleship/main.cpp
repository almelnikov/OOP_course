#include "interface.h"

using namespace std;

int transform_letter(const string str)
{
	if ((str == "а") || (str == "А"))
		return 0;
	else if ((str == "б") || (str == "Б"))
		return 1;
	else if ((str == "в") || (str == "В"))
		return 2;
	else if ((str == "г") || (str == "Г"))
		return 3;
	else if ((str == "д") || (str == "Д"))
		return 4;
	else if ((str == "е") || (str == "Е"))
		return 5;
	else if ((str == "ж") || (str == "Ж"))
		return 6;
	else if ((str == "з") || (str == "З"))
		return 7;
	else if ((str == "и") || (str == "И"))
		return 8;
	else if ((str == "к") || (str == "К"))
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

	if (field.check_win())
		return false;
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

bool check_unsunked(GameField &field, int x, int y)
{
	vector <vector <Cell> > cells = field.get_cells();

	if (cells[x][y].return_state() != CELL_SHIP_M)
		return false;
	if ((!field.is_marked(x, y + 1) && field.in_field(x, y + 1)) ||
	    (!field.is_marked(x, y - 1) && field.in_field(x, y - 1)) ||
		(!field.is_marked(x + 1, y ) && field.in_field(x + 1, y)) ||
		(!field.is_marked(x - 1, y ) && field.in_field(x - 1, y)))
		return true;
	else
		return false;
}

bool computer_turn(GameField &field)
{
	//vector <vector <Cell> > cells = field.get_cells();
	int x = 0, y = 0;
	bool flag_unsunked = false;
	bool ship_flag;

	for (int i = 0; (i < 10) && !flag_unsunked; i++) {
		for (int j = 0; j < 10; j++) {
			if (check_unsunked(field, i, j)) {
				x = i;
				y = j;
				flag_unsunked = true;
				break;
			}	
		}
	}
	if (flag_unsunked) {
		if (!field.is_marked(x, y + 1) && field.in_field(x, y + 1))
			y++;
		else if (!field.is_marked(x, y - 1) && field.in_field(x, y - 1))
			y--;
		else if (!field.is_marked(x + 1, y ) && field.in_field(x + 1, y))
			x++;
		else if (!field.is_marked(x - 1, y ) && field.in_field(x - 1, y))
			x--;
	}
	else {
		do {
			x = rand() % 10;
			y = rand() % 10;
		} while (field.is_marked(x, y));
	}
	ship_flag = field.is_ship(x, y);
	field.mark_cell(x, y);
	return ship_flag;
}

int main()
{
	GameField player, computer;
	bool player_win = false, comp_win = false;

	srand(time(NULL));
	player.randomize_ships();
	computer.randomize_ships();
	refresh_interface(player, computer);
	
	while (!player_win && !comp_win) {
		do {
			 refresh_interface(player, computer);
		} while (player_turn(computer));
		player_win = player.check_win();
		if (player_win)
			break;
		do {
		} while (computer_turn(player));
		comp_win = computer.check_win();
	}
	clr_scr();
	if (player_win) {
		cout << "Вы победили" << endl;
	}
	else {
		cout << "Победил компьютер" << endl;
	}
	return 0;
}
