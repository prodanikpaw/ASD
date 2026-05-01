#pragma once
#include <string>
#include <iostream>
#include "../lib_Heap/Heap.h"

template<typename T>
struct PriorityNode {
    T data;
    int priority; 
    int order;

    PriorityNode(const T& d = T(), int p = 3, int o = 0);

    bool operator<(const PriorityNode<T>& other) const;
    bool operator>(const PriorityNode<T>& other) const;
    bool operator==(const PriorityNode<T>& other) const;

    friend std::ostream& operator<<(std::ostream& os, const PriorityNode<T>& node) {
        os << node.data << "(" << node.priority << ")";
        return os;
    }
};

template<typename T>
class PriorityQueue {
private:
    Heap<PriorityNode<T>> heap;
    int nextOrder;

public:
    PriorityQueue();

    void push(const T& data, int priority);
    void pop();
    T top() const;
    T extractTop();
    bool empty() const;
    int size() const;
    void print() const;
};


template<typename T>
PriorityNode<T>::PriorityNode(const T& d, int p, int o)
    : data(d), priority(p), order(o) {
}

template<typename T>
bool PriorityNode<T>::operator<(const PriorityNode<T>& other) const {
    if (priority != other.priority)
        return priority < other.priority;
    return order < other.order;
}

template<typename T>
bool PriorityNode<T>::operator>(const PriorityNode<T>& other) const {
    return other < *this;
}

template<typename T>
bool PriorityNode<T>::operator==(const PriorityNode<T>& other) const {
    return data == other.data &&
        priority == other.priority &&
        order == other.order;
}


template<typename T>
PriorityQueue<T>::PriorityQueue() : nextOrder(0) {}

template<typename T>
void PriorityQueue<T>::push(const T& data, int priority) {
    heap.insert(PriorityNode<T>(data, priority, nextOrder++));
}

template<typename T>
void PriorityQueue<T>::pop() {
    if (!heap.isEmpty()) {
        heap.erase();
    }
}

template<typename T>
T PriorityQueue<T>::top() const {
    return heap.top().data;
}

template<typename T>
T PriorityQueue<T>::extractTop() {
    return heap.extractTop().data;
}

template<typename T>
bool PriorityQueue<T>::empty() const {
    return heap.isEmpty();
}

template<typename T>
int PriorityQueue<T>::size() const {
    return heap.size();
}

template<typename T>
void PriorityQueue<T>::print() const {
    heap.print();
}
