#ifndef _GAME_LOGIC_HEADER
#define _GAME_LOGIC_HEADER

#include <iostream>
#include <vector>

class Ship;
class GameField;

enum cell_state {
	CELL_EMPTY,
	CELL_EMPTY_M,
	CELL_SHIP,
	CELL_SHIP_M
};

struct FieldCell {
	cell_state state;
	Ship *ptr;
};

class Ship {
	public:
		Ship(int s);
		void hit();
		int cells();
		int get_decks();

	private:
		int _cells;
		int _max_cells;
};

class GameField {
	public:
		GameField();
		bool mark_cell(int x, int y);
		std::vector <std::vector <cell_state> > get_cells();
		bool place_ship(int size, int x, int y, bool vertical);

	private:
		static const int _size = 10;
		FieldCell _field[_size][_size];
		//std::vector <std::vector <FieldCell> > _field;

		void reset();
};

#endif
