#include <iostream>
#include <stdexcept>

using namespace std;

/* Example from Meyers S. More Effective C++*/

class RCObject {
public:
   RCObject();
   RCObject(const RCObject&);
   RCObject& operator=(const RCObject& rhs) {return *this;};
   virtual ~RCObject() = 0;
   void add_reference();
   void remove_reference();
   void mark_unshareable();
   int refcnt() {return ref_count;}
   bool is_shareable() const {return shareable;}
   bool is_shared() const {return (ref_count > 1);}
 
private:
   int ref_count;
   bool shareable;
};

RCObject::RCObject() : ref_count(0), shareable(true) {
}

RCObject::RCObject(const RCObject&) : ref_count(0), shareable(true) {
}

RCObject::~RCObject() {}
 
void RCObject::add_reference() 
{
   ++ref_count;
}
 
void RCObject::remove_reference()
{
   if (--ref_count == 0) delete this;
}
 
void RCObject::mark_unshareable()
{
   shareable = false;
}

/*----End of class RCObject----*/

template<class T>
class RCPtr {
public:
   RCPtr(T* realPtr = 0);
   RCPtr(const RCPtr& rhs);
   ~RCPtr();
   RCPtr& operator=(const RCPtr& rhs);
   T* operator->() const;
   T& operator*() const;
 
private:
   T *pointee;
   void init();
};
 
template<class T>
void RCPtr<T>::init()
{
	if (pointee == 0) return;
   
	if (pointee->is_shareable() == false) {
		pointee = new T(*pointee);
	}
	pointee->add_reference();
}
 
template<class T>
RCPtr<T>::RCPtr(T* realPtr) : pointee(realPtr)
{
   init();
}
 
template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs) : pointee(rhs.pointee)
{ 
   init();
}
 
template<class T>
RCPtr<T>::~RCPtr()
{
   if (pointee) pointee->remove_reference();
}
 
template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
	if (pointee != rhs.pointee) {
		T *oldPointee = pointee;
		pointee = rhs.pointee;
		init(); 
		if (oldPointee) oldPointee->remove_reference();
	}
   
	return *this;
}
 
template<class T>
T* RCPtr<T>::operator->() const 
{
   return pointee;
}
 
template<class T>
T& RCPtr<T>::operator*() const
{
   return *pointee;
}

/*----End of class RCPTR----*/

template <typename Type>
class Array {
private:
	static const int DefaultArraySize = 10;
	class ArrayValue : public RCObject{
	private:
		static const int DefaultArraySize = 10;

	public:
		int _size;
		Type *ia;
		ArrayValue(int sz = DefaultArraySize);
		ArrayValue(const Type *array, int sz);
		ArrayValue(const Array &iarr);
		~ArrayValue() {delete [] ia;};
		void init(const Type *array, int sz);
	};
	RCPtr <ArrayValue> value;

public:
	Array(int sz = DefaultArraySize) : value (new ArrayValue(sz)) {}
	Array(const Type *array, int sz) : value (new ArrayValue(array, sz)) {}
	//Array(const Array &iarr) : value (new ArrayValue(iarr)) {}
	~Array() {};
	Type &operator[](int index);
	bool operator==(const Array &rhs);
	bool operator!=(const Array &rhs);
	//Array &operator=(const Array &rhs);
	int size() {return value->_size;}
	int show_cnt() {return value->refcnt();}

	void print();

	template <typename T>
	friend ostream &operator<<(ostream &os, const Array<T> &arr);

	template <typename T>
	friend istream &operator>>(istream &is, const Array<T> &arr);

};

template <typename Type>
void Array<Type>::ArrayValue::init(const Type *array, int sz)
{
	if (sz > 0 && sz <= 1000000) {
		_size = sz;
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
			throw runtime_error("cannot allocate memory");
		}
	}
	else {
		cerr << "Size of Array is zero, negative or exceed 1000000\n";
		throw length_error("length is not valid");
	}
}


template <typename Type>
Array<Type>::ArrayValue::ArrayValue(const Type *array, int sz)
{
	init(array, sz);
}

template <typename Type>
Array<Type>::ArrayValue::ArrayValue(const Array &iarr)
{
	init(iarr.value->ia, iarr.value->_size);
}


template <typename Type>
Array<Type>::ArrayValue::ArrayValue(int sz)
{
	init(NULL, sz);
}

template <typename Type>
Type &Array<Type>::operator[](int index)
{
	if ((index < 0) || (index >=  value->_size)) 
		throw out_of_range("value out of range");
	if (value->is_shared()) {
		value = new ArrayValue(value->ia, value->_size);
	}
	value->mark_unshareable();
	return value->ia[index];
}

template <typename Type>
bool Array<Type>::operator==(const Array &rhs)
{
	if (value->_size != rhs.value->_size)
		return false;
	for (int i = 0; i < value->_size; i++)
		if (value->ia[i] != rhs.value->ia[i])
			return false;
	return true;
}

template <typename Type>
bool Array<Type>::operator!=(const Array &rhs)
{
	if (value->_size != rhs.value->_size)
		return true;
	for (int i = 0; i < value->_size; i++)
		if (value->ia[i] == rhs.value->ia[i])
			return true;
	return false;
}
/*
template <typename Type>
Array<Type> &Array<Type>::operator=(const Array &rhs)
{
	if (value->_size != rhs.value->_size) {
		cerr << "Cannot assign array, arrays have different size!\n";
		throw invalid_argument("different sizes");
	}
	for (int i = 0; i < value->_size; i++)
		value->ia[i] = rhs.value->ia[i];
	return *this;
}
*/

template <typename T>
ostream &operator<<(ostream &os, const Array<T> &arr)
{
	for (int i = 0; i < arr.value->_size; i++) {
		os << arr.value->ia[i] << ' ';
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
	for (int i = 0; i < arr.value->_size; i++) {
		is >> arr.value->ia[i];
		if (!is.good()) {
			cerr << "Cannot read " << i << " argument to Array" << endl;
			break;
		}
	}
	is.clear();
	return is;
}

template <typename Type>
void Array<Type>::print()
{
	for (int i = 0; i < value->_size; i++)
		cout << value->ia[i] << ' ';
	cout << endl;
}

int main()
{
	const double dbarr[7] = {10, 10.34, -7.23, 1e10, 23, 12.01, 220};

	Array <int> array_def;
	cout << "Default constructor in main fuction: \n";
	array_def.print();

	cout << "\nDouble Array:\n";
	Array <double> array_db1(dbarr, 7);
	cout << array_db1 << endl;

	// Assign tests
	Array <double> array_db2(array_db1);
	array_db2.print();
	cout << "array_db1 cnt after call of copy constructor " <<
		 array_db1.show_cnt() << endl;
	cout << "array_db1 == array_db2? " << (array_db1 == array_db2) << endl;
	cout << "array_db2[1] = 0\n";
	array_db2[1] = 0;
	cout << "array_db1 == array_db2? " << (array_db1 == array_db2) << endl;
	array_db2.print();
	cout << "array_db1 cnt " <<  array_db1.show_cnt() << endl;
	Array <double> newarr(7);
	newarr = array_db1;
	cout << "Result of assign " << newarr << endl;
	cout << "Assigment exeption test:" << endl;
	Array <double> array_db3(1);
	try {
		array_db3 = array_db1;
	}
	catch (invalid_argument err) {
		cerr << err.what() << endl;
	}

	Array <int> readtest(5);
	cin >> readtest;
	cout << readtest << endl;
	
	return 0;
}
