#include <iostream>

using namespace std;

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
		goto_xy(x, y + i);
		cout << " " << i + 1;
	}
	goto_xy(x, y + 9);
	cout << "10";
}

void refresh_interface()
{
	print_int_letters(5, 1);
	print_int_letters(29, 1);
	print_int_numbers(2, 1);
	print_int_numbers(25, 1);
	cout.flush();
}

int main()
{
	clr_scr();
	refresh_interface();
	//goto_xy(5, 6);
	//cout.flush();
	//cout << "afdafdaf" << endl;
	//print_square('*', 10, 10);

	return 0;
}