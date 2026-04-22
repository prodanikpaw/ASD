#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
//#include "TVector.h"
#include "../lib_TVector/Tvector.h"
#include "List.h"
#include "../lib_ITable/ITable.h"

template<typename TValue>
class HashTableC : public ITable<std::string, TValue> {
private:
    TVector<List<std::pair<std::string, TValue>>> _rows;
    int _size;

    size_t h(const std::string& key) const;

public:
    HashTableC(size_t capacity = 10);
    ~HashTableC();

    void insert(const std::string& key, const TValue& val) override;
    void erase(const std::string& key) override;
    TValue find(const std::string& key) const override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const std::string& key) const noexcept override;
    void replace(const std::string& key, const TValue& val) override;

    int getSize() const noexcept;
    void clear();
};

template<typename TValue>
size_t HashTableC<TValue>::h(const std::string& key) const {
    size_t hash_value = 0;
    for (auto sym : key) {
        hash_value += sym;
    }
    return hash_value % _rows.getsize();
}

template<typename TValue>
HashTableC<TValue>::HashTableC(size_t capacity) : _size(0) {
    _rows = TVector<List<std::pair<std::string, TValue>>>(capacity);
    for (int i = 0; i < _rows.getsize(); i++) {
        _rows[i] = List<std::pair<std::string, TValue>>();
    }
}

template<typename TValue>
HashTableC<TValue>::~HashTableC() {}

template<typename TValue>
void HashTableC<TValue>::insert(const std::string& key, const TValue& val) {
    size_t index = h(key);

    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
        if ((*it).first == key) {
            throw std::logic_error("Key already exists: " + key);
        }
    }
    _rows[index].push_back({ key, val });
    _size++;
}

template<typename TValue>
void HashTableC<TValue>::erase(const std::string& key) {
    size_t index = h(key);

    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
        if ((*it).first == key) {
            _rows[index].pop(it.get_current());
            _size--;
            return;
        }
    }
}

template<typename TValue>
TValue HashTableC<TValue>::find(const std::string& key) const {
    size_t index = h(key);

    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
        if ((*it).first == key) {
            return (*it).second;
        }
    }

    throw std::logic_error("Key not found");
}

template<typename TValue>
std::ostream& HashTableC<TValue>::print(std::ostream& out) const noexcept {
    for (int i = 0; i < _rows.getsize(); i++) {
        out << "Bucket " << i << ": ";
        for (auto it = _rows[i].begin(); it != _rows[i].end(); ++it) {
            out << "[" << (*it).first << ":" << (*it).second << "] -> ";
        }
        out << "null" << std::endl;
    }
    return out;
}

template<typename TValue>
bool HashTableC<TValue>::is_empty() const noexcept {
    return _size == 0;
}

template<typename TValue>
bool HashTableC<TValue>::consist(const std::string& key) const noexcept {
    size_t index = h(key);

    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
        if ((*it).first == key) {
            return true;
        }
    }
    return false;
}

template<typename TValue>
void HashTableC<TValue>::replace(const std::string& key, const TValue& val) {
    size_t index = h(key);

    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
        if ((*it).first == key) {
            (*it).second = val;
            return;
        }
    }

    throw std::logic_error("Key not found for replacement");
}

template<typename TValue>
int HashTableC<TValue>::getSize() const noexcept {
    return _size;
}

template<typename TValue>
void HashTableC<TValue>::clear() {
    for (int i = 0; i < _rows.getsize(); i++) {
        while (!_rows[i].is_empty()) {
            _rows[i].pop_front();
        }
    }
    _size = 0;
}