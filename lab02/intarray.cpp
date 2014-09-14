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
	int size();
	int count();
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
		try {
			ia = new int[_size];
			++_count;
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
			cerr << "Cannot allocate memory for IntArray:" << ba.what() << endl;
			ia = NULL;
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

int IntArray::size()
{
	return _size;
}

int IntArray::count()
{
	return _count;
}

int &IntArray::operator[](int index)
{
	if ((index >= 0) && (index < _size)) 
		return ia[index];
	else {
		cerr << "Array index is not in range 0..." << _size << endl;
		return ia[0];
	}
}


void IntArray::print()
{
	for (int i = 0; i < _size; i++)
		cout << ia[i] << ' ';
	cout << endl;
}

int main()
{
	const int carr[8] = {1, 2, 3, 4, 5, 101, 23, -12};
	int iarr[8] = {10, 11, 12, 13, 14, 15, 16, 17};

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
	IntArray array_big(1024 * 1024 * 1024);
	cout << "Number of existing class members: " << def_arr.count() << endl;
	// Operator []
	cout << "4? " << array_c[3] << endl;

	return 0;
}
