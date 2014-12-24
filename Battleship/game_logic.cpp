#include "game_logic.h"

using namespace std;

class EmptyCell : public CellState {
	public:
		virtual char player_char() {return ' ';}
		virtual char computer_char() {return ' ';}
		virtual bool is_marked() {return false;}
};

class EmptyCellM : public CellState {
	public:
		virtual char player_char() {return '.';}
		virtual char computer_char() {return '.';}
		virtual bool is_marked() {return true;}
};

class ShipCell : public CellState {
	public:
		virtual char player_char() {return '0';}
		virtual char computer_char() {return 'a';} //tmp
		virtual bool is_marked() {return false;}
};

class ShipCellM : public CellState {
	public:
		virtual char player_char() {return 'X';}
		virtual char computer_char() {return 'X';}
		virtual bool is_marked() {return true;}
};

Cell::Cell()
{
	_state = new EmptyCell;
	_type = CELL_EMPTY;
}

Cell::~Cell()
{
	//delete _state;
}

char Cell::player_char()
{
	return _state->player_char();
}

char Cell::computer_char()
{
	return _state->computer_char();
}

bool Cell::is_marked()
{
	return _state->is_marked();
}

cell_state Cell::return_state()
{
	return _type;
}

void Cell::clear()
{
	delete _state;
	_state = new EmptyCell;
	_type = CELL_EMPTY;
}

void Cell::set_ship()
{
	delete _state;
	_state = new ShipCell;
	_type = CELL_SHIP;
}

bool Cell::mark() {
	if (_type == CELL_SHIP_M || _type == CELL_EMPTY_M)
		return false;
	if (_type == CELL_SHIP) {
		delete _state;
		_state = new ShipCellM;
		_type = CELL_SHIP_M;
	}
	else {
		delete _state;
		_state = new EmptyCell;
		_type = CELL_EMPTY_M;
	}
	return true;
}

//-------------------------------
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
	_ships.clear();
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			_field[i][j].cell.clear();
			//_field[i][j].state = CELL_EMPTY;
			_field[i][j].ptr = 0;
			_field[i][j].accessible = true;
		}
	}
}

bool GameField::mark_cell(int x, int y)
{
	bool res = false;

	if ((x >= _size) || (x >= _size))
		return false;
	res = _field[x][y].cell.mark();
	if (_field[x][y].cell.return_state() == CELL_SHIP_M)
		_field[x][y].ptr->hit();
	/*
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
	*/
	return res;
}

vector <vector <Cell> > GameField::get_cells()
{
	vector <vector <Cell> > cells;
	cells.resize(_size);
	for (int i = 0; i < _size; i++) {
		cells[i].resize(_size);
		for (int j = 0; j < _size; j++) {
			cells[i][j] = _field[i][j].cell; //fix
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

	if (vertical) {
		for (int i = 0; i < size; i++) {
			if (!_field[x][y + i].accessible)
				return false;
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			if (!_field[x + i][y].accessible)
				return false;
		}
	}

	Ship *ptr = new Ship(size);
	_ships.push_back(ptr);
	mark_ship(size, x, y, vertical, ptr);
	/*
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
	*/
	return true;
}

bool GameField::in_field(int x, int y)
{
	return ((x >= 0) && (x < _size) && (y >= 0) && (y < _size));
}


bool GameField::mark_ship(int size, int x, int y, bool vertical, Ship *ptr)
{
	if (vertical) {
		for (int i = 0; i < size; i++) {
			_field[x][y + i].cell.set_ship();

			//_field[x][y + i].state = CELL_SHIP;
			_field[x][y + i].ptr = ptr;
		}
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= (y + size); j++) {
				if (in_field(x + i, y + j))
					_field[x + i][y + j].accessible = false;
			}
	}
	else {
		for (int i = 0; i < size; i++) {
			_field[x + i][y].cell.set_ship();

			//_field[x + i][y].state = CELL_SHIP;
			_field[x + i][y].ptr = ptr;
		}
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= size; j++) {
				if (in_field(x + j, y + i))
					_field[x + j][y + i].accessible = false;
			}
	}
}

int GameField::get_ships_cnt(int size)
{
	int cnt = 0;
	for (size_t i = 0; i < _ships.size(); i++)
		if (_ships[i]->get_decks() == size)
			cnt++;
	return cnt;
}

void GameField::randomize_ships()
{
	const int ships_cnt = 10;
	const int sizes[ships_cnt] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
	bool placed_flag;

	reset();
	for (int i = 0; i < ships_cnt; i++) {
		do {
			placed_flag = place_ship(sizes[i], rand() % 10, rand() % 10, rand() % 2);
		} while(!placed_flag);
	}
}
