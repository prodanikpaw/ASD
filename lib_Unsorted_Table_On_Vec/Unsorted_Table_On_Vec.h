#pragma once

#include "ITable.h"
#include <iostream>
#include "Tvector.h"

template<typename TKey, typename TValue>
class Unsorted_Table_On_Vec : public ITable <TKey, TValue> {
    TVector<std::pair<TKey, TValue>> _rows;

    int find_position(const TKey& key) const;

public:
    Unsorted_Table_On_Vec() {}
    ~Unsorted_Table_On_Vec() {}

    TValue find(const TKey& key) const override;
    void insert(const TKey& key, const TValue& val) override;
    void erase(const TKey& key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& key) const noexcept override;
    int size() const noexcept;
    void replace(const TKey& key, const TValue& val) override;

    void clear();
};

template<typename TKey, typename TValue>
int Unsorted_Table_On_Vec<TKey, TValue>::find_position(const TKey& key) const {
    for (int i = 0; i < _rows.getsize(); ++i) {
        if (_rows[i].first == key) {
            return i;
        }
    }
    return -1;
}

template<typename TKey, typename TValue>
TValue Unsorted_Table_On_Vec<TKey, TValue>::find(const TKey& key) const {
    int pos = find_position(key);
    if (pos != -1) {
        return _rows[pos].second;
    }
    return TValue();
}

template<typename TKey, typename TValue>
void Unsorted_Table_On_Vec<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    int pos = find_position(key);
    if (pos != -1) {
        
        throw std::invalid_argument("Key already exists in the table");
    }
    else {
        _rows.push_back(std::make_pair(key, val));
    }
}

template<typename TKey, typename TValue>
void Unsorted_Table_On_Vec<TKey, TValue>::erase(const TKey& key) {
    int pos = find_position(key);
    if (pos != -1) {
        _rows.erase(pos);
    }
}

template<typename TKey, typename TValue>
std::ostream& Unsorted_Table_On_Vec<TKey, TValue>::print(std::ostream& out) const noexcept {
    out << "Unsorted Table Contents:" << std::endl;
    out << "========================" << std::endl;

    if (_rows.getsize() == 0) {
        out << "Table is empty" << std::endl;
    }
    else {
        for (int i = 0; i < _rows.getsize(); ++i) {
            out << "  [" << i << "] " << _rows[i].first
                << " -> " << _rows[i].second << std::endl;
        }
    }

    out << "========================" << std::endl;
    out << "Total elements: " << _rows.getsize() << std::endl;

    return out;
}

template<typename TKey, typename TValue>
bool Unsorted_Table_On_Vec<TKey, TValue>::is_empty() const noexcept {
    return _rows.getsize() == 0;
}

template<typename TKey, typename TValue>
bool Unsorted_Table_On_Vec<TKey, TValue>::consist(const TKey& key) const noexcept {
    return find_position(key) != -1;
}

template<typename TKey, typename TValue>
int Unsorted_Table_On_Vec<TKey, TValue>::size() const noexcept {
    return _rows.getsize();
}

template<typename TKey, typename TValue>
void Unsorted_Table_On_Vec<TKey, TValue>::replace(const TKey& key, const TValue& val) {
    int pos = find_position(key);
    if (pos != -1) {
        _rows[pos].second = val;
    }
}

template<typename TKey, typename TValue>
void Unsorted_Table_On_Vec<TKey, TValue>::clear() {
    while (_rows.getsize() > 0) {
        _rows.pop_back();
    }
}

