#include <iostream>
#include <new>

using namespace std;

class IntArray {
public:
	explicit IntArray(int sz = DefaultArraySize);
	IntArray(const int *array, int sz);
	IntArray(const IntArray &iarr);
	~IntArray();
	int &operator[](int index);
	int size() {return _size;};
	int count() {return _count;};
	int cnt_entrances(int elem);
	void print();

private:
	static const int DefaultArraySize = 10;
	int _size;
	int *ia;
	static int _count;
	void init(const int *array, int sz);
};

int IntArray::_count = 0;

void IntArray::init(const int *array, int sz)
{
	if (sz > 0) {
		_size = sz;
		++_count;
		try {
			ia = new int[_size];
			if (array != NULL) {
				for (int i = 0; i < _size; i++)
					ia[i] = array[i];
			}
			else {
				for (int i = 0; i < _size; i++)
					ia[i] = 0;
			}
		}
		catch (bad_alloc& ba) {
			cerr << "Cannot allocate memory for IntArray: " << ba.what() << endl;
			ia = NULL;
			_size = 0;
		}
	}
	else {
		cerr << "Size of IntArray is zero or negative!\n";
	}
}

IntArray::IntArray(const int *array, int sz)
{
	init(array, sz);
}

IntArray::IntArray(const IntArray &iarr)
{
	init(iarr.ia, iarr._size);
}

IntArray::IntArray(int sz)
{
	init(NULL, sz);
}

IntArray::~IntArray()
{
	--_count;
	delete [] ia;
}

int &IntArray::operator[](int index)
{
	if ((index >= 0) && (index < _size)) 
		return ia[index];
	else {
		cerr << "Array index is not in range 0.." << _size << endl;
		return ia[0];
	}
}

int IntArray:: cnt_entrances(int elem)
{
	int cnt = 0;

	for (int i = 0; i < _size; i++)
		if (ia[i] == elem)
			++cnt;
	return cnt;
}


void IntArray::print()
{
	for (int i = 0; i < _size; i++)
		cout << ia[i] << ' ';
	cout << endl;
}

void run_tests()
{
	const int carr[8] = {1, 2, 3, 4, 5, 101, 23, -12};
	int iarr[8] = {10, 11, 12, 12, 14, 15, 12, 17};

	cout << "Begin of run_tests function, create 6 IntArrays\n\n";
	// Default constructor
	IntArray def_arr;
	cout << "Default constructor:\n";
	def_arr.print();
	cout << def_arr.size() << endl;
	// Size only
	cout << "Initialization with size only:\n";
	IntArray array4(4);
	array4.print();
	cout << "Number of existing class members: " << def_arr.count() << endl;
	// Integer array
	cout << "Initialization using array:\n";
	IntArray array_i(iarr, 8);
	array_i.print();
	// Const array
	cout << "Initialization using const array:\n";
	IntArray array_c(carr, 8);
	array_c.print();
	// IntArray object
	cout << "Initialization using another IntArray object:\n";
	IntArray array_copy(array_c);
	array_copy.print();
	// Trying to create 1G elements array
	cout << "Initialization of 1G elements array\n";
	IntArray array_big(1024 * 1024 * 1024);
	// Operator []
	cout << "array_c[3] = 4? " << array_c[3] << endl;
	cout << "array_c[3] = -120\n";
	array_c[3] = -120;
	cout << "array_c[3] = " << array_c[3] << endl;
	cout << "Trying access wrong element index: " << array_c[1000] << endl;
	// cnt_entrances tests
	cout << "cnt_entrances test array: ";
	array_i.print();
	cout << "Elem '12': " << array_i.cnt_entrances(12) << endl;
	cout << "Elem '14': " << array_i.cnt_entrances(14) << endl;
	cout << "Elem '100': " << array_i.cnt_entrances(100) << endl;
	// Destructor and count tests
	cout << "Number of existing class members: " << def_arr.count() << endl;
	cout << "End of run_tests function\n\n";
}

int main()
{
	IntArray array_def;
	cout << "Default constructor in main fuction: \n";
	array_def.print();
	run_tests();
	cout << "Number of existing class members: " << array_def.count() << endl;
	return 0;
}