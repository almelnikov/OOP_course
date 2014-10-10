#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

string &remove_punct(string &str)
{
	string list_punct("'\n,.:;(){}[]");
	int is_mark = 1;
	
	while (!str.empty() && is_mark) {
		// Require C++11
		if (list_punct.find(str.back()) != string::npos)
			str.pop_back();
		else
			is_mark = 0;
	}
	return str;
}

int main(int argc, char *argv[])
{
	ifstream wordsfile;
	fstream text;
	ofstream output;
	string buf;
	set <string> ingored_words;
	string str1("asdf,.");
	string str2("qwerty");

	if (argc != 4) {
		cerr << "Uncorrect command line arguments!" << endl;
		return -1;
	}
	wordsfile.open(argv[1]);
	if (!wordsfile) {
		cerr << "Cannot open file: " << argv[1] << endl;
		return -1;
	}
	text.open(argv[2], ios_base::in | ios_base::out);
	if (!text) {
		cerr << "Cannot open file: " << argv[2] << endl;
		return -1;
	}
	output.open(argv[3]);
	if (!output) {
		cerr << "Cannot open file: " << argv[3] << endl;
		return -1;
	}
	
	while (wordsfile >> buf) {
		ingored_words.insert(buf);
	}
	
	wordsfile.close();
	text.close();
	output.close();
	
	return 0;
}