#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int count_lines(ifstream &input, ofstream &output)
{
	int lines_cnt = 0;
	string line;

	while (getline(input, line)) {
		++lines_cnt;
		output << line << '\n';
	}
	return lines_cnt;
}

void process_files(vector <string> filenames, ofstream &output)
{
	ifstream input;
	int lines_cnt;

	for (int i = 0; i < filenames.size(); i++) {
		input.open(filenames[i].c_str());
		if (!input.is_open()) {
			cerr << "Cannot open file: " << filenames[i] << endl;
			input.clear();
			continue;
		}
		lines_cnt = count_lines(input, output);
		cout << lines_cnt << " lines in file: " << filenames[i] << endl;
		input.close();
	}
}

int main(int argc, char *argv[])
{
	ifstream namesfile;
	ofstream output;
	vector <string> filenames;
	string name;

	if (argc != 3) {
		cerr << "Uncorrect command line arguments!\n";
		return -1;
	}
	namesfile.open(argv[1]);
	if (!namesfile.is_open()) {
		cerr << "Cannot open file: " << argv[1] << endl;
		return -2;
	}
	output.open(argv[2]);
	if (!output.is_open()) {
		cerr << "Cannot open file: " << argv[2] << endl;
		return -2;
	}
	while (namesfile >> name) {
		filenames.push_back(name);
	}
	process_files(filenames, output);
	namesfile.close();
	output.close();
	return 0;
}