#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include "list.h"
#include "ITable.h"

template<typename TKey, typename TValue>
class UnsortedTableOnList : public ITable<TKey, TValue> {
private:
    List<std::pair<TKey, TValue>> items; 

    typename List<std::pair<TKey, TValue>>::Iterator find_iterator(const TKey& key) const {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->first == key) {
                return it;
            }
        }
        return items.end();
    }
public:
    UnsortedTableOnList() = default;
    UnsortedTableOnList(const UnsortedTableOnList& other);
    ~UnsortedTableOnList() = default;

    UnsortedTableOnList& operator=(const UnsortedTableOnList& other);

    void insert(const TKey& key, const TValue& val) override;
    void erase(const TKey& key) override;
    TValue find(const TKey& key) const override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& key) const noexcept override;
    void replace(const TKey& key, const TValue& val) override;

    int size() const noexcept;
    void clear();
};

template<typename TKey, typename TValue>
UnsortedTableOnList<TKey, TValue>::UnsortedTableOnList(const UnsortedTableOnList& other): items(other.items) {}

template<typename TKey, typename TValue>
UnsortedTableOnList<TKey, TValue>&UnsortedTableOnList<TKey, TValue>::operator=(const UnsortedTableOnList& other) {
    if (this != &other) {
        items = other.items;
    }
    return *this;
}

template<typename TKey, typename TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    if (find_iterator(key) != items.end()) {
        throw std::invalid_argument("Key already exists in the table");
    }
    items.push_back(std::make_pair(key, val));
}

template<typename TKey, typename TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
    auto it = find_iterator(key);
    if (it != items.end()) {
        items.pop(it.get_current());
    }
    else {
        throw std::invalid_argument("Key not found in the table");
    }
}

template<typename TKey, typename TValue>
TValue UnsortedTableOnList<TKey, TValue>::find(const TKey& key) const {
    auto it = find_iterator(key);
    if (it != items.end()) {
        return it->second;
    }
    throw std::invalid_argument("Key not found in the table");
}

template<typename TKey, typename TValue>
std::ostream& UnsortedTableOnList<TKey, TValue>::print(std::ostream& out) const noexcept {
    out << "Unsorted Table On List Contents (using std::pair):" << std::endl;
    out << "---------------------------------------------------" << std::endl;

    int index = 0;
    for (auto it = items.begin(); it != items.end(); ++it, ++index) {
        out << "[" << index << "] Key: " << it->first
            << " -> Value: " << it->second << std::endl;
    }

    out << "Total items: " << items.size() << std::endl;
    return out;
}

template<typename TKey, typename TValue>
bool UnsortedTableOnList<TKey, TValue>::is_empty() const noexcept {
    return items.is_empty();
}

template<typename TKey, typename TValue>
bool UnsortedTableOnList<TKey, TValue>::consist(const TKey& key) const noexcept {
    return find_iterator(key) != items.end();
}

template<typename TKey, typename TValue>
void UnsortedTableOnList<TKey, TValue>::replace(const TKey& key, const TValue& val) {
    auto it = find_iterator(key);
    if (it != items.end()) {
        it->second = val;
    }
    else {
        throw std::invalid_argument("Key not found in the table");
    }
}


template<typename TKey, typename TValue>
int UnsortedTableOnList<TKey, TValue>::size() const noexcept {
    return items.size();
}

template<typename TKey, typename TValue>
void UnsortedTableOnList<TKey, TValue>::clear() {
    while (!items.is_empty()) {
        items.pop_front();
    }
}