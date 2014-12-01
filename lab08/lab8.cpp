#include <iostream>
#include <string>

using namespace std;

class Animal {
	public:
		Animal() {}
		virtual ~Animal() {}
		void print_specie() {
			cout << _specie << endl;
		}
		virtual void act() {
			cout << "Это ";
			print_specie();
		}

	protected:
		string _specie;
};

class Carp : public Animal {
	public:
	Carp() {
		_specie = "карп";
	}
	~Carp() {
		cout << "Карп умер" << endl;
	};
};

class Duck : public Animal {
	public:
	Duck() {
		_specie = "уточка";
	}
	void act() {
		cout << "Кря-кря-кря" << endl;
	}
};



int main()
{
	static const int animals_cnt = 3;
	Animal *animals[animals_cnt];

	animals[0] = new Animal;
	animals[1] = new Carp;
	animals[2] = new Duck;
	
	for (int i = 0; i < animals_cnt; i++)
		animals[i]->act();

	Carp carp;	
	return 0;
}