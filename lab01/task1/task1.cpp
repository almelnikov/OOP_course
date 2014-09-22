#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void test_streambits(istream &stream)
{
	if (stream.bad())
		cout << "Bad stream" << endl;
	if (stream.fail())
		cout << "Stream fail" << endl;
	if (stream.eof())
		cout << "End of file" << endl;
	if (stream.good())
		cout << "Good" << endl;
}

istream &print_2cout(istream &stream)
{
	string str;
	
	while (stream >> str, stream.good()) {
		cout << str << endl;
	}
	test_streambits(stream);
	stream.clear();
	return stream;
}

int main()
{
	/*
	cin.setstate(ios_base::badbit);
	cin.setstate(ios_base::failbit);
	*/
	print_2cout(cin);
	cout << "\nClear:" << endl;
	test_streambits(cin);
	/*
	cin.setstate(ios_base::failbit);
	test_streambits(cin);
	cin.setstate(ios_base::goodbit);
	test_streambits(cin);
	*/
	return 0;
}