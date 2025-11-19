#include <stdexcept>
#include "list.h" 

template <class T>
class lstqueue {
    List<T> _queue;

public:
    lstqueue();
    lstqueue(const lstqueue<T>& other);
    ~lstqueue();

    lstqueue<T>& operator=(const lstqueue<T>& other);

    void push(const T& val) noexcept;
    void pop();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    bool is_empty() const noexcept;
    int size() const noexcept;
    void clear() noexcept;
};

template <class T>
lstqueue<T>::lstqueue() : _queue() {}

template <class T>
lstqueue<T>::lstqueue(const lstqueue<T>& other) : _queue(other._queue) {}

template <class T>
lstqueue<T>::~lstqueue() {
}

template <class T>
lstqueue<T>& lstqueue<T>::operator=(const lstqueue<T>& other) {
    if (this != &other) {
        _queue = other._queue;
    }
    return *this;
}

template <class T>
void lstqueue<T>::push(const T& val) noexcept {
    _queue.push_back(val); 
}

template <class T>
void lstqueue<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    _queue.pop_front();
}

template <class T>
T& lstqueue<T>::front() {
    if (is_empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    return *_queue.begin();
}

template <class T>
const T& lstqueue<T>::front() const {
    if (is_empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    return *_queue.begin();
}

template <class T>
T& lstqueue<T>::back() {
    if (is_empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    auto it = _queue.begin();
    auto prev = it;
    while (it != _queue.end()) {
        prev = it;
        ++it;
    }
    return *prev;
}

template <class T>
const T& lstqueue<T>::back() const {
    if (is_empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    auto it = _queue.begin();
    auto prev = it;
    while (it != _queue.end()) {
        prev = it;
        ++it;
    }
    return *prev;
}

template <class T>
bool lstqueue<T>::is_empty() const noexcept {
    return _queue.is_empty();
}

template <class T>
int lstqueue<T>::size() const noexcept {
    return _queue.size();
}

template <class T>
void lstqueue<T>::clear() noexcept {
    while (!is_empty()) {
        pop();
    }
}