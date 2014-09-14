#include <fstream>
#include <iostream>
#include <string>

using namespace std;

istream &print_2cout(istream &stream)
{
	string str;

	while (getline(stream, str)) {
		cout << str << "\n";
	}
	stream.clear();
	return stream;
}

int main()
{
	print_2cout(cin);
	return 0;
}