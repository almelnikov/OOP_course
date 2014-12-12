#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class FileBuf
{
	public:
		void copy(string filename) {
			ifstream file;
			file.open(filename.c_str());
			if (!file) 
				cerr << "Не удалось открыть файл " << filename << endl;
			else {
				string line;
				_buf.clear();
				while (getline(file, line)) {
					_buf.push_back(line);
				}
				file.close();
			}
		}
		void paste(string filename) {
			ofstream file;
			file.open(filename.c_str(), ios::out | ios::trunc);
			if (!file) 
				cerr << "Не удалось открыть файл " << filename << endl;
			else {
				file.close();
			}
		}
		void print() {
			if (_buf.empty()) {
				cout << "Буфер пуст" << endl;
			}
			else {
				for (size_t i = 0; i < _buf.size(); i++)
					cout << _buf[i] << endl;
			}
		}

	private:
		vector <string> _buf;
};
/*
class BaseCommand {
	public:
		BaseCommand() {}
		virtual ~BaseCommand() {}
		virtual void execute() = 0;
};
*/
class Command {
	public:
		Command(FileBuf *p) : _ptr(p) {}
		virtual ~Command() {}
		virtual void execute() = 0;

	protected:
		FileBuf * _ptr;
};

class CopyCommand : public Command
{
	public:
		CopyCommand(FileBuf *p) : Command(p) {}
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
		PasteCommand(FileBuf *p) : Command(p) {}
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
		PrintCommand(FileBuf *p) : Command(p) {}
		void execute() {
			cout << "Содержимое буфера:" << endl;
			_ptr->print();
		}
};

class MacroCommand : public Command
{
	public:
		MacroCommand() : Command(0) {}
		void add(Command *cmd) {
			_cmds.push_back(cmd);
		}
		void execute() {
			for (size_t i = 0; i < _cmds.size(); i++)
				_cmds[i]->execute();
		}
		
	private:
		vector <Command*> _cmds;
};

int main()
{
	FileBuf filebuf;
	MacroCommand macro;

	macro.add(new CopyCommand(&filebuf));
	macro.add(new PrintCommand(&filebuf));
	macro.add(new PasteCommand(&filebuf));
	macro.add(new CopyCommand(&filebuf));
	macro.add(new PasteCommand(&filebuf));
	macro.add(new PasteCommand(&filebuf));
	macro.execute();
	return 0;
}