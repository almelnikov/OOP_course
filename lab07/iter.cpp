#include <iostream>
#include <stdexcept>

using namespace std;

template <typename Type>
class Array {
public:
	explicit Array(int sz = DefaultArraySize);
	Array(const Type *array, int sz);
	Array(const Array &iarr);
	~Array();
	Type &operator[](int index);
	bool operator==(const Array &rhs);
	bool operator!=(const Array &rhs);
	Array &operator=(const Array &rhs);
	int size() {return _size;};
	int count() {return _count;};
	void print();
	void print_even();
	void print_odd();

	template <typename T>
	friend ostream &operator<<(ostream &os, const Array<T> &arr);

	template <typename T>
	friend istream &operator>>(istream &is, const Array<T> &arr);


private:
	static const int DefaultArraySize = 10;
	int _size;
	Type *ia;
	static int _count;
	void init(const Type *array, int sz);
};


template <typename Type>
int Array<Type>::_count = 0;

template <typename Type>
void Array<Type>::init(const Type *array, int sz)
{
	if (sz > 0 && sz <= 1000000) {
		_size = sz;
		++_count;
		try {
			ia = new Type[_size];
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
			cerr << "Cannot allocate memory for Array: " << ba.what() << endl;
			ia = NULL;
			_size = 0;
			throw runtime_error("cannot allocate memor");
		}
	}
	else {
		cerr << "Size of Array is zero, negative or exceed 1000000\n";
		throw length_error("length is not valid");
	}
}

template <typename Type>
Array<Type>::Array(const Type *array, int sz)
{
	init(array, sz);
}

template <typename Type>
Array<Type>::Array(const Array &iarr)
{
	init(iarr.ia, iarr._size);
}

template <typename Type>
Array<Type>::Array(int sz)
{
	init(NULL, sz);
}

template <typename Type>
Array<Type>::~Array()
{
	--_count;
	delete [] ia;
}

template <typename Type>
Type &Array<Type>::operator[](int index)
{
	if ((index >= 0) && (index < _size)) 
		return ia[index];
	else {
		cerr << "Array index is not in range 0.." << _size << endl;
		throw out_of_range("value out of range");
	}
}

template <typename Type>
bool Array<Type>::operator==(const Array &rhs)
{
	if (_size != rhs._size)
		return false;
	for (int i = 0; i < _size; i++)
		if (ia[i] != rhs.ia[i])
			return false;
	return true;
}

template <typename Type>
bool Array<Type>::operator!=(const Array &rhs)
{
	if (_size != rhs._size)
		return true;
	for (int i = 0; i < _size; i++)
		if (ia[i] != rhs.ia[i])
			return true;
	return false;
}

template <typename T>
ostream &operator<<(ostream &os, const Array<T> &arr)
{
	for (int i = 0; i < arr._size; i++) {
		os << arr.ia[i] << ' ';
		if (!os.good()) {
			cerr << "Cannot write " << i << " argument from Array" << endl;
			os.clear();
			break;
		}
	}
	return os;
}

template <typename T>
istream &operator>>(istream &is, const Array<T> &arr)
{
	for (int i = 0; i < arr._size; i++) {
		is >> arr.ia[i];
		if (!is.good()) {
			cerr << "Cannot read " << i << " argument to Array" << endl;
			break;
		}
	}
	is.clear();
	return is;
}

template <typename Type>
Array<Type> &Array<Type>::operator=(const Array &rhs)
{
	if (_size != rhs._size) {
		cerr << "Cannot assign array, arrays have different size!\n";
		throw invalid_argument("different sizes");
	}
	for (int i = 0; i < _size; i++)
		ia[i] = rhs.ia[i];
	return *this;
}

template <typename Type>
void Array<Type>::print()
{
	for (int i = 0; i < _size; i++)
		cout << ia[i] << ' ';
	cout << endl;
}

template <typename Type>
void Array<Type>::print_even()
{
	for (int i = 0; i < _size; i += 2)
		cout << ia[i] << ' ';
	cout << endl;
}


template <typename Type>
void Array<Type>::print_odd()
{
	if (_size < 2)
		return;
	for (int i = 1; i < _size; i += 2)
		cout << ia[i] << ' ';
	cout << endl;
}

int main()
{
	const int iarr[8] = {1, 2, 3, 4, 5, 101, 23, -12};

	cout << "\nInt Array:\n";
	Array <int> array_i(iarr, 8);
	cout << array_i << endl;

	Array <float> array_read(5);
	cin >> array_read;
	cout << array_read << endl;
	return 0;
}