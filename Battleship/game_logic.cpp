#include "game_logic.h"

using namespace std;

Ship::Ship(int s)
{
	_cells = s;
	_max_cells = s;
}

void Ship::hit()
{
	_cells--;
}

int Ship::cells()
{
	return _cells;
}

int Ship::get_decks()
{
	return _max_cells;
}

bool GameField::mark_cell(int x, int y)
{
	bool res = false;

	if ((x >= _size) || (x >= _size))
		return false;
	switch (_field[x][y].state) {
		case CELL_EMPTY_M:
		case CELL_SHIP_M:
			break;

		case CELL_EMPTY:
			_field[x][y].state = CELL_EMPTY_M;
			res = true;
			break;

		case CELL_SHIP:
			_field[x][y].state = CELL_SHIP_M;
			res = true;
			break;
	}
	return res;
}
