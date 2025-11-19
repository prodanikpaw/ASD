#pragma once

#include "list.h"
#include <stdexcept>
template<class T>
class lststack {

	List<T> _stack;
public:
	lststack();
	lststack(const lststack& other);
	~lststack();

    lststack<T>& operator=(const lststack<T>& other);

    void push(const T& val) noexcept;
    void pop();
    T& top();
    const T& top() const;
    bool is_empty() const noexcept;
    int size() const noexcept;
    void clear() noexcept;

};

template <class T>
lststack<T>::lststack() : _stack() {}

template <class T>
lststack<T>::lststack(const lststack<T>& other) : _stack(other._stack) {}

template <class T>
lststack<T>::~lststack() {
    
}


template <class T>
lststack<T>& lststack<T>::operator=(const lststack<T>& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

template <class T>
void lststack<T>::push(const T& val) noexcept {
    _stack.push_front(val);
}

template <class T>
void lststack<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("lststack is empty");
    }
    _stack.pop_front();
}

template <class T>
T& lststack<T>::top() {
    if (is_empty()) {
        throw std::logic_error("lststack is empty");
    }
    return *_stack.begin();
}

template <class T>
const T& lststack<T>::top() const {
    if (is_empty()) {
        throw std::logic_error("lststack is empty");
    }
    return *_stack.begin();
}

template <class T>
bool lststack<T>::is_empty() const noexcept {
    return _stack.is_empty();
}

template <class T>
int lststack<T>::size() const noexcept {
    return _stack.size();
}

template <class T>
void lststack<T>::clear() noexcept {
    while (!is_empty()) {
        pop();
    }
}