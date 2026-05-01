#pragma once

#include <stdexcept>
#include "../lib_TVector/Tvector.h"

template<typename T>
class Heap {
private:
    TVector<T> data;

    int parent(int i) const;
    int _left(int i) const;
    int _right(int i) const;
    void siftUp(int index);
    void siftDown(int index);

public:
    Heap();
    Heap(const TVector<T>& arr);
    void insert(const T& value);
    bool erase();
    T top() const;
    T extractTop();
    bool isEmpty() const;
    int size() const;
    void print() const;
};

template<typename T>
void heapSort(TVector<T>& arr);

template<typename T>
int Heap<T>::parent(int i) const {
    return (i - 1) / 2;
}

template<typename T>
int Heap<T>::_left(int i) const {
    return 2 * i + 1;
}

template<typename T>
int Heap<T>::_right(int i) const {
    return 2 * i + 2;
}

template<typename T>
void Heap<T>::siftUp(int index) {
    while (index > 0) {
        int p = parent(index);

        if (data[index] < data[p]) {
            T temp = data[index];
            data[index] = data[p];
            data[p] = temp;
            index = p;
        }
        else {
            break;
        }
    }
}

template<typename T>
void Heap<T>::siftDown(int index) {
    int size = data.getsize();

    while (true) {
        int left = _left(index);
        int right = _right(index);
        int minIndex = index;

        if (left < size) {
            if (data[left] < data[minIndex]) {
                minIndex = left;
            }
        }

        if (right < size) {
            if (data[right] < data[minIndex]) {
                minIndex = right;
            }
        }

        if (minIndex != index) {
            T temp = data[index];
            data[index] = data[minIndex];
            data[minIndex] = temp;
            index = minIndex;
        }
        else {
            break;
        }
    }
}


template<typename T>
Heap<T>::Heap() {}

template<typename T>
Heap<T>::Heap(const TVector<T>& arr) : data(arr) {
    int size = data.getsize();
    for (int i = size / 2 - 1; i >= 0; i--) {
        siftDown(i);
    }
}

template<typename T>
void Heap<T>::insert(const T& value) {
    data.push_back(value);
    siftUp(data.getsize() - 1);
}

template<typename T>
bool Heap<T>::erase() {
    if (data.getsize() == 0) {
        return false;
    }

    if (data.getsize() == 1) {
        data.pop_back();
        return true;
    }

    data[0] = data.back();
    data.pop_back();
    siftDown(0);

    return true;
}

template<typename T>
T Heap<T>::top() const {
    if (data.getsize() == 0) {
        throw std::logic_error("Heap is empty");
    }
    return data[0];
}

template<typename T>
T Heap<T>::extractTop() {
    if (data.getsize() == 0) {
        throw std::logic_error("Heap is empty");
    }

    T result = data[0];
    data[0] = data.back();
    data.pop_back();

    if (data.getsize() > 0) {
        siftDown(0);
    }

    return result;
}

template<typename T>
bool Heap<T>::isEmpty() const {
    return data.getsize() == 0;
}

template<typename T>
int Heap<T>::size() const {
    return data.getsize();
}

template<typename T>
void Heap<T>::print() const {
    std::cout << data << std::endl;
}

template<typename T>
void heapSort(TVector<T>& arr) {
    if (arr.getsize() <= 1) {
        return;
    }

    Heap<T> heap(arr);
    for (int i = 0; i < arr.getsize(); i++) {
        arr[i] = heap.extractTop();
    }
}