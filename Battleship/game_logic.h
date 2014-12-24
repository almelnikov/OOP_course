#ifndef _GAME_LOGIC_HEADER
#define _GAME_LOGIC_HEADER

#include <iostream>
#include <vector>
#include <cstdlib>

class Ship;
class GameField;
class Cell;
class CellState;

enum cell_state {
	CELL_EMPTY,
	CELL_EMPTY_M,
	CELL_SHIP,
	CELL_SHIP_M
};

class Cell {
	public:
		Cell();
		~Cell();
		bool mark();
		char player_char();
		char computer_char();
		bool is_marked();
		void clear();
		void set_ship();
		cell_state return_state();
		 
	private:
		cell_state _type;
		CellState *_state;
};

class CellState {
	public:
		virtual char player_char() = 0;
		virtual char computer_char() = 0;
		virtual bool is_marked() = 0;
};


struct FieldCell {
	cell_state state;
	Cell cell;
	bool accessible;
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
		std::vector <std::vector <Cell> > get_cells();
		bool place_ship(int size, int x, int y, bool vertical);
		int get_ships_cnt(int size);
		void randomize_ships();

	private:
		static const int _size = 10;
		FieldCell _field[_size][_size];
		std::vector <Ship*> _ships;

		void reset();
		bool in_field(int x, int y);
		bool mark_ship(int size, int x, int y, bool vertical, Ship *ptr);
};

#endif
