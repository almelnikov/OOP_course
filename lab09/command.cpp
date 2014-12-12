#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class FileOps
{
	public:
		void copy(string filename) {
			ifstream file;
			file.open(filename.c_str());
			file.close();
		}
		void paste(string filename) {
			ofstream file;
			file.open(filename.c_str());
			file.close();
		}
		void print() {
			if (_buf.empty()) {
				cout << "Буфер пуст" << endl;
			}
			else {
				for (size_t i = 0; i < _buf.size(); i++)
					cout << _buf[i];
			}
		}

	private:
		vector <string> _buf;
};

class Command {
	public:
		virtual ~Command() {}
		Command(FileOps *p) : _ptr(p) {}
		virtual void execute() = 0;

	protected:
		FileOps * _ptr;
};

class CopyCommand : public Command
{
	public:
		CopyCommand(FileOps *p) : Command(p) {}
		void execute() {
			string str;
			cout << "Введите имя файла для копирования в буфер: ";
			cin >> str;
			_ptr->copy(str);
		}
};

class PasteCommand : public Command
{
	public:
		PasteCommand(FileOps *p) : Command(p) {}
		void execute() {
			string str;
			cout << "Введите имя файла для копирования из буфера: ";
			cin >> str;
			_ptr->paste(str);
		}
};

class PrintCommand : public Command
{
	public:
		PrintCommand(FileOps *p) : Command(p) {}
		void execute() {
			cout << "Содержимое буфера:" << endl;
			_ptr->print();
		}
};

int main()
{

	return 0;
}