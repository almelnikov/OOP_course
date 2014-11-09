#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

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
	bool flag_letter;
	string buf;
	
	if (!str.empty())
		flag_letter = is_letter(str[0]);
	for (it = str.begin(); it != str.end(); ++it) {
		if (is_letter(*it) != flag_letter) {
			strvec.push_back(buf);
			//cout << buf << endl;
			buf.clear();
			buf.push_back(*it);
			flag_letter = !flag_letter;
		}
		else
			buf.push_back(*it);
	}
	strvec.push_back(buf);
	return strvec;
}

string &find_and_replace_str(map <string, string> wordsmap, string &str)
{
	map <string, string>::iterator it = wordsmap.find(str);

	if (it != wordsmap.end()) {
		str = it->second;
	}

	return str;
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
		if (!transformed.eof())
			line.append("\n");
		split_string(file_content, line);
	}
	transformed.close();
	transformed.open(argv[2], ios_base::out | ios_base::trunc);
	for (size_t i = 0; i < file_content.size(); i++) {
		find_and_replace_str(wordsmap, file_content[i]);
		transformed << file_content[i];
	}
	input.close();
	transformed.close();
	
	return 0;
}
