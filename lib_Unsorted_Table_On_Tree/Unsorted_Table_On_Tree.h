#pragma once
#include "Tree.h"
#include <iostream>
#include <stdexcept>

template<typename TKey, typename TValue>
class UnorderedTreeTable {
private:
    Tree<TKey, TValue> tree;

public:
    UnorderedTreeTable() = default;
    ~UnorderedTreeTable() = default;

    void insert(const TKey& key, const TValue& val);
    void erase(const TKey& key);
    TValue find(const TKey& key) const;
    void replace(const TKey& key, const TValue& val);
    bool consist(const TKey& key) const;

    void print() const;
    void printTree() const;
    void printAllTraversals() const;

    int size() const;
    bool empty() const;
    void clear();
};

template<typename TKey, typename TValue>
void UnorderedTreeTable<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    tree.insert(key, val);
}

template<typename TKey, typename TValue>
void UnorderedTreeTable<TKey, TValue>::erase(const TKey& key) {
    tree.erase(key);
}

template<typename TKey, typename TValue>
TValue UnorderedTreeTable<TKey, TValue>::find(const TKey& key) const {
    return tree.find(key);
}

template<typename TKey, typename TValue>
void UnorderedTreeTable<TKey, TValue>::replace(const TKey& key, const TValue& val) {
    tree.replace(key, val);
}

template<typename TKey, typename TValue>
bool UnorderedTreeTable<TKey, TValue>::consist(const TKey& key) const {
    return tree.consist(key);
}

template<typename TKey, typename TValue>
void UnorderedTreeTable<TKey, TValue>::print() const {
    std::cout << "\n=== Таблица ===\n";
    std::cout << "Размер: " << tree.size() << "\n";
    std::cout << "Содержимое (прямой обход):\n";
    tree.print_D1();
    std::cout << "\n=============\n";
}

template<typename TKey, typename TValue>
void UnorderedTreeTable<TKey, TValue>::printTree() const {
    tree.printTree();
}

template<typename TKey, typename TValue>
void UnorderedTreeTable<TKey, TValue>::printAllTraversals() const {
    std::cout << "\n=== 4 обхода ===\n";

    std::cout << "1. Прямой обход (D1): ";
    tree.print_D1();
    std::cout << "\n";

    std::cout << "2. Симметричный обход (D2): ";
    tree.print_D2();
    std::cout << "\n";

    std::cout << "3. Обратный обход (D3): ";
    tree.print_D3();
    std::cout << "\n";

    std::cout << "4. Обход в ширину (W): ";
    tree.print_W();
    std::cout << "\n============\n";
}

template<typename TKey, typename TValue>
int UnorderedTreeTable<TKey, TValue>::size() const {
    return tree.size();
}

template<typename TKey, typename TValue>
bool UnorderedTreeTable<TKey, TValue>::empty() const {
    return tree.empty();
}

template<typename TKey, typename TValue>
void UnorderedTreeTable<TKey, TValue>::clear() {
    tree.clear();
}