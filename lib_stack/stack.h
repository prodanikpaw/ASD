#pragma once
#include <iostream>
#include <stdexcept>

template<class T>
class stack {
	T* _data;
	int _size;
	int _top;

public:
	stack();
	~stack();
	void push(const T& Val);
	void pop();
	T& top();
	bool is_empty() noexcept;
	bool is_full() noexcept;
	void clear() noexcept;
};

template <class T>
stack<T>::stack() : _size(100), _top(-1) { 
	_data = new T[_size];
}

template <class T>
stack<T>::~stack() {
	delete[] _data;
}

template <class T>
void stack<T>::push(const T& Val) { 
	if (is_full())
	{
		throw std::logic_error("stack is full");
	}
	_data[++_top] = Val; 
}

template <class T>
void stack<T>::pop() { 
	if (is_empty())
	{
		throw std::logic_error("stack is empty");
	}
	--_top;
}

template <class T>
T& stack<T>::top() {
	if (is_empty()) { 
		throw std::logic_error("stack is empty");
	}
	return _data[_top];
}

template <class T>
bool stack<T>::is_empty() noexcept { 
	return _top == -1;
}

template <class T>
bool stack<T>::is_full() noexcept { 
	return _top == _size - 1;
}

template <class T>
void stack<T>::clear() noexcept {
	_top = -1;
}