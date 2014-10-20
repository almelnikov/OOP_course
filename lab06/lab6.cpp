#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool is_letter(char c)
{
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
		return true;
	else
		return false;
}

vector <string> &split_string(vector <string> &strvec, string &str)
{
	string::iterator it;
	string::iterator letter_change;
	bool flag_letter = false;
	string buf;
	
	for (it = str.begin(); it != str.end(); ++it) {
		if (is_letter(*it) != flag_letter) {
			if (!strvec.empty())
				strvec.push_back(buf);
			cout << buf << endl;
			buf.clear();
			buf.push_back(*it);
			flag_letter = !flag_letter;
		}
		else
			buf.push_back(*it);
	}
	return strvec;
}

int main(int argc, char *argv[])
{
	ifstream input;
	fstream transformed;
	map <string, string> wordsmap;
	string skey, svalue, line;
	vector <string> file_content;
	
	if (argc != 3) {
		cerr << "Uncorrect command line arguments!" << endl;
		return -1;
	}
	input.open(argv[1]);
	if (!input) {
		cerr << "Cannot open file: " << argv[1] << endl;
		return -1;
	}
	transformed.open(argv[2], ios_base::in | ios_base::out);
	if (!transformed) {
		cerr << "Cannot open file: " << argv[2] << endl;
		return -1;
	}
	
	while (input >> skey >> svalue) {
		wordsmap.insert(pair <string, string> (skey, svalue));
	}
	while (getline(transformed, line)) {
		split_string(file_content, line);
	}
	
	return 0;
}
