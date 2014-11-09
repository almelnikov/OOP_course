#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <iterator>
#include <numeric>

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

class ReplaceStr {
public:
	map <string, string> *wordsmap;
	void operator()(string &str) {
		map <string, string>::iterator it = wordsmap->find(str);

		if (it != wordsmap->end()) {
			str = it->second;
		}
	};
	ReplaceStr(map <string, string> *m) {
		wordsmap = m;
	}
};

class PrintStr {
public:
	fstream *out;
	void operator()(string &str) {
		(*out) << str;
	};
	PrintStr(fstream *os) {
		out = os;
	}
};

class AddToMap {
public:
	map <string, string> *wordsmap;
	void operator()(pair <string, string> &p) {
		wordsmap->insert(p);
	};
	AddToMap(map <string, string> *m) {
		wordsmap = m;
	}
};

vector <string> file_tokenizer(ifstream &input) {
	vector <string> tokens;

	if (input) {
		stringstream iss;
		iss << input.rdbuf();
		copy(istream_iterator<string>(iss), istream_iterator<string>(),
			 back_inserter(tokens));
	}
	return tokens;
}

vector <pair <string, string> > &add_pair(vector <pair <string, string> > &vec,
										  string &str)
{
	string emptystr;

	if (vec.empty()) {
		vec.push_back(pair <string, string> (str, emptystr));
	}
	else {
		size_t last = vec.size() - 1;
		if (vec[last].second.empty()) {
			vec[last].second = str;
		}
		else
			vec.push_back(pair <string, string> (str, emptystr));
	}
	return vec;
}

vector <pair <string, string> > split_on_pairs(vector <string> &vec)
{
	vector <pair <string, string> > res;

	return accumulate(vec.begin(), vec.end(), res, add_pair);
}

int main(int argc, char *argv[])
{
	ifstream keyvalue;
	fstream transformed;
	map <string, string> wordsmap;
	string skey, svalue, line;
	vector <string> file_content;
	
	if (argc != 3) {
		cerr << "Uncorrect command line arguments!" << endl;
		return -1;
	}

	keyvalue.open(argv[1]);
	if (!keyvalue) {
		cerr << "Cannot open file: " << argv[1] << endl;
		return -1;
	}
	transformed.open(argv[2], ios_base::in | ios_base::out);
	if (!transformed) {
		cerr << "Cannot open file: " << argv[2] << endl;
		return -1;
	}
	
	vector <string> keyv_words = file_tokenizer(keyvalue);
	for (size_t i = 0; i < keyv_words.size(); i++)
		cout << keyv_words[i] << ' ';
	vector <pair <string, string> > kvpairs = split_on_pairs(keyv_words);
	for_each(kvpairs.begin(), kvpairs.end(), AddToMap(&wordsmap));
	/*
	while (keyvalue >> skey >> svalue) {
		wordsmap.insert(pair <string, string> (skey, svalue));
	}
	*/
	while (getline(transformed, line)) {
		if (!transformed.eof())
			line.append("\n");
		split_string(file_content, line);
	}
	transformed.close();
	transformed.open(argv[2], ios_base::out | ios_base::trunc);

	for_each(file_content.begin(), file_content.end(), ReplaceStr(&wordsmap));
	for_each(file_content.begin(), file_content.end(), PrintStr(&transformed));

	keyvalue.close();
	transformed.close();
	
	return 0;
}
