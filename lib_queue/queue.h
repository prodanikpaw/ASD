#include <iostream>
#include <stdexcept>


template<class T>
class queue {
    T* _data;
    int _size;
    int _head;
    int _count;

public:
    queue();
    ~queue();
    void push(const T& Val);
    void pop();
    inline T head() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
};

template <class T>
queue<T>::queue() : _size(100), _head(0), _count(0) {
    _data = new T[_size];
}

template <class T>
queue<T>::~queue() {
    delete[] _data;
}

template <class T>
void queue<T>::push(const T& Val) {
    if (is_full()) {
        throw std::logic_error("queue is full");
    }
    int tail = (_head + _count) % _size;
    _data[tail] = Val;
    _count++;
}

template <class T>
void queue<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("queue is empty");
    }
    _head = (++_head) % _size;
    _count--;
}

template <class T>
inline T queue<T>::head() const {
    if (is_empty()) {
        throw std::logic_error("queue is empty");
    }
    return _data[_head];
}

template <class T>
inline bool queue<T>::is_empty() const noexcept {
    return _count == 0;
}

template <class T>
inline bool queue<T>::is_full() const noexcept {
    return _count == _size;
}

template <class T>
void queue<T>::clear() noexcept {
    _head = 0;
    _count = 0;
}
