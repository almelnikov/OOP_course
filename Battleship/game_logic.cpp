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

GameField::GameField()
{
	reset();
}

void GameField::reset()
{
	//_field.resize(_si
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			_field[i][j].state = CELL_EMPTY;
			_field[i][j].ptr = 0;
		}
	}
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
			_field[x][y].ptr->hit();
			res = true;
			break;
	}
	return res;
}

vector <vector <cell_state> > GameField::get_cells()
{
	vector <vector <cell_state> > cells;
	cells.resize(_size);
	for (int i = 0; i < _size; i++) {
		cells[i].resize(_size);
		for (int j = 0; j < _size; j++) {
			cells[i][j] = _field[i][j].state;
		}
	}
	return cells;
}

bool GameField::place_ship(int size, int x, int y, bool vertical)
{
	if ((size > 4) || (size < 1))
		return false;
	if (vertical && ((y + size) > _size))
		return false;
	if (!vertical && ((x + size) > _size))
		return false;

	Ship *ptr = new Ship(size);
	if (vertical) {
		for (int i = 0; i < (y + size); i++) {
			_field[x][y + i].state = CELL_SHIP;
			_field[x][y + i].ptr = ptr;
		}
	}
	else {
		for (int i = 0; i < (y + size); i++) {
			_field[x + i][y].state = CELL_SHIP;
			_field[x + i][y].ptr = ptr;
		}
	}
	return true;
}
