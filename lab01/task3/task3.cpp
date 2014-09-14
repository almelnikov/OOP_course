#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <int> get_linepos(fstream &input)
{
	vector <int> pos_vec;
	int position = 0;
	string line;

	while (getline(input, line)) {
		position += line.length();
		if (!input.eof())
			++position;
		pos_vec.push_back(position);
	}
	input.clear();
	return pos_vec;
}

int main(int argc, char *argv[])
{
	fstream posfile;
	vector <int> pos_vec;

	if (argc != 2) {
		cerr << "Uncorrect command line arguments!\n";
		return -1;
	}
	posfile.open(argv[1]);
	if (!posfile.is_open()) {
		cerr << "Cannot open file: " << argv[1] << endl;
		return -2;
	}
	pos_vec = get_linepos(posfile);
	posfile << '\n';
	for (int i = 0; i < pos_vec.size(); i++) {
		posfile << pos_vec[i] << ' ';
	}
	posfile.close();
	return 0;
}