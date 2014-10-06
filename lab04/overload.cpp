#include <iostream>

using namespace std;

namespace cat {

void func(int a, int b)
{
	cout << "THIS IS CAT!!!!: (int a, int b)\n";
}

/*void func(int a, float b)
{
	cout << "Function call: (int a, float b)\n";
}
*/

void func(int *a, int b, float c)
{
	cout << "Function call: (int *a, int b, float c)\n";
}

void func(istream &a, int b)
{
	cout << "Function call: (iostream &a, int b)\n";
}

void func(int a, float *b)
{
	cout << "Function call: (int a, float *b)\n";
}

void func(double a, double b, double c)
{
	cout << "Function call: (double a, double b, double c)\n";
}

void func(int *a, int b)
{
	cout << "Function call: (int *a, int b)\n";
}

void func(int a, void (*f)(int, int))
{
	cout << "Function call: (int a, void (*f)(int, int))\n";
}

void func(int a, char b, int *c)
{
	cout << "Function call: (int a, char b, int *c)\n";
}

}

using namespace cat;
/*
void func (int a, int b)
{
	cout<< "NO CAT!!!"<<endl;
}
*/

int main()
{
	int n, m;
	float f1;
	
	cout << "func(1, 2);\n";
	func(1, 2);
	cout << "func(1.2, 2);\n";
	func(1.2, 2);
	cout << "func(&n, m, f1);\n";
	cout << "func(cin, n);\n";
	func(cin, n);
	cout << "func(1, 2, 3.14);\n";
	func(1, 2, 3.14);
	cout << "func(n, &f1);\n";
	func(n, &f1);
	cout << "func(1e8, 10, f1);\n";
	func(1e8, 10, f1);
	cout << "func(&n, 140);\n";
	func(&n, 140);
	cout << "func(0, &func);\n";
	func(0, &func);
	cout << "func(n, 'a', &n);\n";
	func(n, 'a', &n);
	cout << "func(23, f1);\n";
	func(23, f1);
	
	return 0;
}