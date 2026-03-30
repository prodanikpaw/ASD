#pragma once
#include <iostream>

using namespace std;

#define STEP_OF_CAPACITY 15

template<typename T>
class TVector {
protected:
	T* _data;
	int _size;
	int _capacity;
public:
	TVector();
	TVector(T* data, int size);
	TVector(int size);
	TVector(const TVector& other);
	TVector(std::initializer_list<T> data);

	~TVector();


	class Iterator {
	private:
		T* _ptr;
	public:
		Iterator(T* ptr = nullptr) : _ptr(ptr) {}

		T& operator*() const {
			return *_ptr;
		}

		Iterator& operator++() {
			++_ptr;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++_ptr;
			return temp;
		}

		Iterator& operator--() {
			--_ptr;
			return *this;
		}

		Iterator operator--(int) {
			Iterator temp = *this;
			--_ptr;
			return temp;
		}

		Iterator operator+(int n) const {
			return Iterator(_ptr + n);
		}

		Iterator operator-(int n) const {
			return Iterator(_ptr - n);
		}

		int operator-(const Iterator& other) const {
			return _ptr - other._ptr;
		}

		Iterator& operator+=(int n) {
			_ptr += n;
			return *this;
		}

		Iterator& operator-=(int n) {
			_ptr -= n;
			return *this;
		}

		bool operator==(const Iterator& other) const {
			return _ptr == other._ptr;
		}

		bool operator!=(const Iterator& other) const {
			return _ptr != other._ptr;
		}

		bool operator<(const Iterator& other) const {
			return _ptr < other._ptr;
		}

		bool operator>(const Iterator& other) const {
			return _ptr > other._ptr;
		}

		bool operator<=(const Iterator& other) const {
			return _ptr <= other._ptr;
		}

		bool operator>=(const Iterator& other) const {
			return _ptr >= other._ptr;
		}

		T& operator[](int n) const {
			return _ptr[n];
		}
	};

	Iterator begin() noexcept { return Iterator(_data); }

	Iterator end() noexcept { return Iterator(_data + _size); }

	Iterator begin() const noexcept { return Iterator(_data); }

	Iterator end() const noexcept { return Iterator(_data + _size); }

	//getters
	inline T& front();
	inline T& back();
	inline const T& front() const;
	inline const T& back()const;
	inline T* getdata()const noexcept;
	inline int getsize()const noexcept;
	inline int getcapacity()const noexcept;

	void push_front(T val);
	void push_back(T val);
	void insert(int pos, T val);
	void erase(int pos, T val);
	T pop_front();
	T pop_back();
	T erase(int pos);

	inline T& operator[](int indx) noexcept;
	inline const T& operator[](int indx)const noexcept;


	void reallocate(size_t new_capacity);
	void resize(int new_size);

	int find_first(T val) const;
	int find_last(T val) const;
	TVector<int> find_all(T val) const;

	TVector<T>& operator=(const TVector<T>& other);

	bool operator==(const TVector<T>& other) const;
	bool operator!=(const TVector<T>& other) const;
	bool operator<(const TVector<T>& other) const;
	bool operator>(const TVector<T>& other) const;
	bool operator<=(const TVector<T>& other) const;
	bool operator>=(const TVector<T>& other) const;


	template<typename U>
	friend ostream& operator<<(std::ostream& os, const TVector<U>& vec);
private:
	void repacking();
};

template<typename T>
TVector<T>::TVector() : _data(nullptr), _size(0), _capacity(0) {}


template<typename T>
TVector<T>::TVector(T* data, int size) {
	if (size < 0) {
		throw std::invalid_argument("Size cannot be negative");
	}

	_capacity = (size + STEP_OF_CAPACITY) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
	_size = size;
	_data = new T[_capacity];

	for (int i = 0; i < _size; i++) {
		_data[i] = data[i];
	}
}

template<typename T>
TVector<T>::TVector(int size) {
	_capacity = (size + STEP_OF_CAPACITY) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
	_size = size;
	_data = new T[_capacity];
	for (int i = 0;i < _size; i++)
	{
		_data[i] = T();
	}
}

template<typename T>
TVector<T>::TVector(const TVector& other) {
	_capacity = other.getcapacity();
	_size = other.getsize();
	_data = new T[_capacity];
	for (int i = 0;i < _size;i++)
	{
		_data[i] = other[i];
	}
}


template<typename T>
TVector<T>::TVector(std::initializer_list<T> data) {
	_size = data.size();
	_capacity = (_size + STEP_OF_CAPACITY) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
	_data = new T[_capacity];
	for (int i = 0;i < _size; i++)
	{
		_data[i] = *(data.begin() + i);
	}
}

template<typename T>
TVector<T>::~TVector() {
	if (_data != nullptr)
	{
		delete[] _data;
		_data = nullptr;
	}
}

template<typename T>
inline T& TVector<T>::front() {
	if (_size < 1)
	{
		throw std::logic_error("Vector is empty");
	}
	return _data[0];
}

template<typename T>
inline T& TVector<T>::back() {
	if (_size < 1)
	{
		throw std::logic_error("Vector is empty");
	}
	return _data[_size - 1];
}

template<typename T>
inline const T& TVector<T>::front() const {
	if (_size < 1)
	{
		throw std::logic_error("Vector is empty");
	}
	return _data[0];
}

template<typename T>
inline const T& TVector<T>::back() const {
	if (_size < 1)
	{
		throw std::logic_error("Vector is empty");
	}
	return _data[_size - 1];;
}



template<typename T>
void TVector<T>::push_front(T val)
{
	if (_size + 1 > _capacity) {
		reallocate(_capacity + STEP_OF_CAPACITY);
	}
	for (size_t i = _size; i > 0; i--) {
		_data[i] = _data[i - 1];
	}

	_data[0] = val;
	_size++;
}



template<typename T>
void TVector<T>::push_back(T val)
{
	if (_size + 1 > _capacity) {
		reallocate(_capacity + STEP_OF_CAPACITY);
	}

	_data[_size] = val;
	_size++;

}

template<typename T>
void TVector<T>::insert(int pos, T val)
{
	if (pos < 0 || pos > _size) {
		throw std::out_of_range("Index out of range");
	}
	if (_size + 1 > _capacity) {
		reallocate(_capacity + STEP_OF_CAPACITY);
	}
	else {
		for (int i = _size; i > pos; i--) {
			_data[i] = _data[i - 1];
		}
	}
	_data[pos] = val;
	_size++;
}


template<typename T>
T TVector<T>::pop_front()
{
	if (_size < 1)
	{
		throw std::logic_error("Vector is empty");
	}
	T value = _data[0];
	for (int i = 0; i < _size - 1; i++) {
		_data[i] = _data[i + 1];
	}
	_size--;
	repacking();
	return value;
}

template<typename T>
T TVector<T>::pop_back()
{
	if (_size < 1)
	{
		throw std::logic_error("Vector is empty");
	}
	_size--;
	T value = _data[_size];
	repacking();
	return value;
}

template<typename T>
T TVector<T>::erase(int pos)
{
	if (pos < 0 || pos >= _size) {
		throw std::out_of_range("Index out of range");
	}
	T value = _data[pos];
	for (int i = pos;i < _size - 1;i++)
	{
		_data[i] = _data[i + 1];
	}
	_size--;
	repacking();
	return value;
}

template<typename T>
inline T* TVector<T>::getdata() const noexcept { return _data; }

template<typename T>
inline int TVector<T>::getsize() const noexcept { return _size; }

template<typename T>
inline int TVector<T>::getcapacity() const noexcept { return _capacity; }

template<typename T>
inline T& TVector <T>::operator[](int indx)noexcept {
	return _data[indx];
}
template<typename T>
inline const T& TVector <T>::operator[](int indx)const noexcept {
	return _data[indx];
}


template<typename T>
void TVector<T>::resize(int new_size) {
	if (new_size < 0)
	{
		throw std::logic_error("Size cannot be negativey");
	}
	if (new_size > _capacity)
	{
		_capacity = (new_size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
		T* new_data = new T[_capacity];

		for (int i = 0;i < _size;i++)
		{
			new_data[i] = _data[i];
		}

		for (int i = _size; i < new_size; i++) {
			new_data[i] = T();
		}
		delete[]_data;
		_data = new_data;
	}
	else if (new_size > _size)
	{
		for (int i = _size; i < new_size; i++) {
			_data[i] = T();
		}
	}
	_size = new_size;
}

template<typename T>
void TVector<T>::reallocate(size_t new_capacity)
{
	if (new_capacity < _size) {
		new_capacity = _size;
	}

	_capacity = new_capacity;
	T* new_data = new T[_capacity];


	for (size_t i = 0; i < _size; i++) {
		new_data[i] = _data[i];
	}

	delete[] _data;
	_data = new_data;
}


template<typename T>
void TVector<T>::repacking() {
	if (_capacity - _size > STEP_OF_CAPACITY * 2) {
		int new_capacity = (_size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;

		if (new_capacity < STEP_OF_CAPACITY) {
			new_capacity = STEP_OF_CAPACITY;
		}
		T* new_data = new T[new_capacity];

		for (int i = 0; i < _size; i++) {
			new_data[i] = _data[i];
		}
		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;
	}
}

template <typename T>
int TVector<T>::find_first(T val) const
{
	for (int i = 0;i < _size;i++)
	{
		if (_data[i] == val)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
int TVector<T>::find_last(T val) const {
	for (int i = _size - 1; i >= 0; i--) {
		if (_data[i] == val) {
			return i;
		}
	}
	return -1;
}

template <typename T>
TVector<int> TVector<T>::find_all(T val) const
{
	TVector<int> positions;

	for (int i = 0; i < _size; i++)
	{
		if (_data[i] == val)
		{
			positions.push_back(i);
		}
	}
	return positions;
}


template<typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
	if (this == &other) {
		return *this;
	}

	if (_data == nullptr && other._data == nullptr)
	{
		return *this;
	}
	if (_size != other._size)
	{
		if (_data != nullptr)
		{
			delete[] _data;
		}
		_size = other._size;
		_capacity = other._capacity;
		_data = new T[_capacity];
	}

	for (int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}

	return *this;
}




template<typename T>
bool TVector<T>::operator==(const TVector<T>& other) const {
	if (_size != other._size) {
		return false;
	}
	for (int i = 0; i < _size; i++)
	{
		if (_data[i] != other._data[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool TVector<T>::operator!=(const TVector<T>& other)const {
	return !(*this == other);
}

template<typename T>
bool TVector<T>::operator<(const TVector<T>& other)const
{
	if (_size == other._size)
	{
		for (int i = 0; i < _size; i++) {
			if (_data[i] < other._data[i]) {
				return true;
			}
			if (_data[i] > other._data[i]) {
				return false;
			}
		}
	}
	return _size < other._size;
}

template<typename T>
bool TVector<T>::operator>(const TVector<T>& other) const {
	return other < *this;
}
template<typename T>
bool TVector<T>::operator<=(const TVector<T>& other) const {
	return !(other < *this);
}

template<typename T>
bool TVector<T>::operator>=(const TVector<T>& other) const {
	return !(*this < other);
}

template<typename T>
ostream& operator<<(ostream& os, const TVector<T>& vec) {
	os << "[";
	for (int i = 0; i < vec.getsize(); i++) {
		os << vec[i];
		if (i < vec.getsize() - 1) {
			os << ", ";
		}
	}
	os << "]";
	return os;
}

