#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ios::pos_type get_filesize(fstream &file)
{
	ios::pos_type size;

	file.seekg(0, ios_base::end);
	size = file.tellg();
	file.clear();
	return size;
}

void get_linepos(fstream &inout)
{
	ios::pos_type size;
	int cnt = 0;
	char ch;

	size = get_filesize(inout);
	inout << endl;
	inout.seekg(0);
	while (inout.get(ch) && (cnt <= size)) {
		cnt++;
		if (ch == '\n') {
			ios::pos_type position = inout.tellg();
			inout << cnt << ' ';
			inout.seekg(position);
		}
	}
	inout.clear();
	inout << cnt << endl;
}

int main(int argc, char *argv[])
{
	fstream posfile;
	long filesize;

	if (argc != 2) {
		cerr << "Uncorrect command line arguments!\n";
		return -1;
	}
	posfile.open(argv[1], ios_base::in | ios_base::out | ios_base::app);
	if (!posfile.is_open()) {
		cerr << "Cannot open file: " << argv[1] << endl;
		return -2;
	}
	get_linepos(posfile);
	posfile.close();
	return 0;
}