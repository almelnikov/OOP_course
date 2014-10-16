#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

string &remove_punct(string &str)
{
	static const string list_punct("'\",.:;(){}[]-!?\\/");
	string::iterator iter = str.begin();
	string::iterator iter_end = str.end();
	
	while (iter != iter_end) {
		string::size_type pos = 0;
		while ((pos = str.find_first_of(list_punct, pos)) != string::npos)
			str.erase(pos, 1);
		iter++;
	}
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

void print_words_cnt(ofstream &output, vector <string> &words,
					 vector <string> &sorted)
{
	vector <string>::iterator it;

	for (int i = 0; i < words.size(); i++) {
		int cnt = 0;
		
		it = lower_bound(sorted.begin(), sorted.end(), words[i]);
		for (; it != sorted.end(); ++it)
			if (*it == words[i])
				++cnt;
			else
				break;
		if (cnt != 0)
			output << words[i] << ' ' << cnt << endl;
	}
}

bool cmp_strlen(string a, string b)
{
	return (a.size() < b.size());
}

void print_sorted_length(fstream &output, vector <string> &words)
{
	vector <string>::iterator it;
	vector <string> sorted;
	
	output.clear();
	output.seekp(0);
	sorted = words;
	stable_sort(sorted.begin(), sorted.end(), cmp_strlen);
	for (it = sorted.begin(); it != sorted.end(); ++it)
		if ((*it).size() >= 3)
			break;
	for (; it != sorted.end(); ++it)
		output << *it <<endl;
}

int main(int argc, char *argv[])
{
	ifstream wordsfile;
	fstream text;
	ofstream output;
	string buf;
	set <string> ingored_words;
	vector <string> words, sorted_words, unique_words;
	vector <string>::iterator unique_end;

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
	output.open(argv[3], ios_base::out | ios_base::trunc);
	if (!output) {
		cerr << "Cannot open file: " << argv[3] << endl;
		return -1;
	}
	
	while (wordsfile >> buf) {
		ingored_words.insert(buf);
	}

	while (text >> buf) {
		remove_punct(buf);
		if ((ingored_words.find(buf) == ingored_words.end()) && !buf.empty())
			words.push_back(buf);
	}

	sorted_words = words;
	sort(sorted_words.begin(), sorted_words.end());
	unique_words = sorted_words;
	unique_end = unique(unique_words.begin(), unique_words.end());
	unique_words.resize(distance(unique_words.begin(), unique_end));

	print_words_cnt(output, unique_words, sorted_words);

	text.close();
	text.open(argv[2], ios_base::out | ios_base::trunc);
	print_sorted_length(text, unique_words);

	wordsfile.close();
	text.close();
	output.close();
	
	return 0;
}