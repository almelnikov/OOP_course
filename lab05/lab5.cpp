#include <fstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream wordsfile, text;
	ofstream output;
	string buf;
	set <string> ingored_words;

	if (argc != 4) {
		cerr << "Uncorrect command line arguments!" << endl;
		return -1;
	}
	wordsfile.open(argv[1]);
	if (!wordsfile) {
		cerr << "Cannot open file: " << argv[1] << endl;
		return -1;
	}
	text.open(argv[2]);
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