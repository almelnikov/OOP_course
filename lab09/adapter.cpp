#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class StringReader {
	public:
		string get_lower_cin() {
			string str;
			cin >> str;
			transform(str.begin(), str.end(), str.begin(), ::tolower);
			return str;
		}
		string get_upper_cin() {
			string str;
			cin >> str;
			transform(str.begin(), str.end(), str.begin(), ::toupper);
			return str;
		}
};

class StringGetter {
	public:
		virtual ~StringGetter() {}
		virtual string get_lower() = 0;
		virtual string get_upper() = 0;
};

class Adapter : public StringGetter, private StringReader {
	public:
		Adapter() {}
		string get_lower() {
			return "STRING: " + get_lower_cin();
		}
		string get_upper() {
			return "STRING: " + get_upper_cin();
		}
};

int main()
{
	string str;
	StringGetter *ptr = new Adapter();
	str = ptr->get_lower();
	cout << str << endl;
	str = ptr->get_upper();
	cout << str << endl;
	return 0;
}