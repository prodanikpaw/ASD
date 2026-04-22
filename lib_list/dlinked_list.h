#pragma once
#include <stdexcept>

template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node(T val, Node<T>* nxt = nullptr, Node<T>* prv = nullptr)
        : value(val), next(nxt), prev(prv) {}
};

template <class T>
class DLinkedList {
    Node<T>* _head;
    Node<T>* _tail;
    int _count;

public:
    DLinkedList();
    DLinkedList(const DLinkedList<T>& other);
    ~DLinkedList();

    DLinkedList<T>& operator=(const DLinkedList<T>& other);

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(int pos, const T& val);
    void insert(Node<T>* node, const T& val);

    void pop_front();
    void pop_back();
    void pop(int pos);
    void pop(Node<T>* node);

    bool is_empty() const;
    Node<T>* find(const T& val);
    int size() const;

    class Iterator {
        Node<T>* current;
    public:
        Iterator() : current(nullptr) {};
        Iterator(Node<T>* pos) : current(pos) {};
        Iterator(const Iterator& other) : current(other.current) {};

        Iterator& operator=(const Iterator& other) {
            if (this != &other) { current = other.current; }
            return *this;
        }

        T& operator*() {
            if (current == nullptr) {
                throw std::logic_error("Dereferencing null iterator");
            }
            return current->value;
        }

        const T& operator*() const {
            if (current == nullptr) {
                throw std::logic_error("Dereferencing null iterator");
            }
            return current->value;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() { 
            current = current->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        Iterator& operator-=(int n) {
            for (int i = 0; i < n && current != nullptr; ++i) {
                current = current->prev;
            }
            return *this;
        }

        Iterator& operator+=(int n) {
            for (int i = 0; i < n && current != nullptr; ++i) {
                current = current->next;
            }
            return *this;
        }

        Node<T>* get_current() const { return current; }
    };

    // Методы для итераторов
    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }
    Iterator begin() const { return Iterator(_head); }
    Iterator end() const { return Iterator(nullptr); }

    // Методы для обратного обхода
    Iterator rbegin() { return Iterator(_tail); }
    Iterator rend() { return Iterator(nullptr); }
    Iterator rbegin() const { return Iterator(_tail); }
    Iterator rend() const { return Iterator(nullptr); }
};

template <class T>
DLinkedList<T>::DLinkedList() : _head(nullptr), _tail(nullptr), _count(0) {}


template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& other) {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;

    Node<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}


template <class T>
DLinkedList<T>::~DLinkedList() {
    while (!is_empty()) {
        pop_front();
    }
}


template <class T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList<T>& other) {
    if (this != &other) {
        while (!is_empty()) {
            pop_front();
        }

        Node<T>* current = other._head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}


template <class T>
void DLinkedList<T>::push_front(const T& val) noexcept {
    Node<T>* newNode = new Node<T>(val, _head, nullptr);

    if (_head == nullptr) {
        _head = _tail = newNode;
    }
    else {
        _head->prev = newNode;
        _head = newNode;
    }
    _count++;
}


template <class T>
void DLinkedList<T>::push_back(const T& val) noexcept {
    Node<T>* newNode = new Node<T>(val);

    if (_tail == nullptr) {
        _head = _tail = newNode;
    }
    else {
        _tail->next = newNode;
        newNode->prev = _tail;
        _tail = newNode;
    }
    _count++;
}

// Вставка 
template <class T>
void DLinkedList<T>::insert(int pos, const T& val) {
    if (pos < 0 || pos > _count) {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0) {
        push_front(val);
    }
    else if (pos == _count) {
        push_back(val);
    }
    else {
        
        if (pos < _count / 2) {
            Node<T>* current = _head;
            for (int i = 0; i < pos - 1; i++) {
                current = current->next;
            }

            Node<T>* newNode = new Node<T>(val, current->next, current);
            current->next->prev = newNode;
            current->next = newNode;
        }
        else {
            Node<T>* current = _tail;
            for (int i = _count - 1; i > pos; i--) {
                current = current->prev;
            }

            Node<T>* newNode = new Node<T>(val, current, current->prev);
            current->prev->next = newNode;
            current->prev = newNode;
        }

        _count++;
    }
}


template <class T>
void DLinkedList<T>::insert(Node<T>* node, const T& val) {
    if (node == nullptr) {
        push_back(val);
        return;
    }

    if (node == _head) {
        push_front(val);
    }
    else {
       
        Node<T>* newNode = new Node<T>(val, node, node->prev);
        node->prev->next = newNode;
        node->prev = newNode;
        _count++;
    }
}


template <class T>
void DLinkedList<T>::pop_front() {
    if (_head == nullptr) return;

    Node<T>* temp = _head;
    _head = _head->next;

    if (_head == nullptr) {
        _tail = nullptr;
    }
    else {
        _head->prev = nullptr;
    }

    delete temp;
    _count--;
}

//
template <class T>
void DLinkedList<T>::pop_back() {
    if (_tail == nullptr) return;

    if (_head == _tail) {
        delete _head;
        _head = _tail = nullptr;
    }
    else {
        Node<T>* temp = _tail;
        _tail = _tail->prev;
        _tail->next = nullptr;
        delete temp;
    }
    _count--;
}

// 
template <class T>
void DLinkedList<T>::pop(int pos) {
    if (pos < 0 || pos >= _count) {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0) {
        pop_front();
    }
    else if (pos == _count - 1) {
        pop_back();
    }
    else {
        
        Node<T>* toDelete;
        if (pos < _count / 2) {
            toDelete = _head;
            for (int i = 0; i < pos; i++) {
                toDelete = toDelete->next;
            }
        }
        else {
            toDelete = _tail;
            for (int i = _count - 1; i > pos; i--) {
                toDelete = toDelete->prev;
            }
        }

        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;

        delete toDelete;
        _count--;
    }
}



template <class T>
void DLinkedList<T>::pop(Node<T>* node) {
    if (node == nullptr) return;

    if (node == _head) {
        pop_front();
    }
    else if (node == _tail) {
        pop_back();
    }
    else {
        
        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node;
        _count--;
    }
}

template <class T>
bool DLinkedList<T>::is_empty() const {
    return _head == nullptr;
}


template <class T>
Node<T>* DLinkedList<T>::find(const T& val) {
    Node<T>* current = _head;
    while (current != nullptr) {
        if (current->value == val) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <class T>
int DLinkedList<T>::size() const {
    return _count;
}