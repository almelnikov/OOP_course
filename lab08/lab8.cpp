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

class LeggedAnimal : public Animal {
public:
	LeggedAnimal() {}
	void print_legs() {
		cout << "Лап " <<_legs << endl;
	}
	void act() {
		print_specie();
		print_legs();
		cout << endl;
	}
private:
	int _legs;
};

class Duck : public LeggedAnimal {
public:
	Duck() {
		_specie = "уточка";
	}
	void print_specie() {
		cout << _specie << "!!!" << endl;
	}
	void act() {
		cout << "Кря-кря-кря" << endl;
		print_specie();
		cout << endl;
	}
};

class Dog : public LeggedAnimal {
public:
	Dog() {
		_specie = "собака";
	}
};

int main()
{
	static const int animals_cnt = 4;
	Animal *animals[animals_cnt];

	animals[0] = new Animal;
	animals[1] = new Carp;
	animals[2] = new Duck;
	animals[3] = new Dog;
	
	for (int i = 0; i < animals_cnt; i++)
		animals[i]->act();

	Carp carp;
	return 0;
}