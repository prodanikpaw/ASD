#pragma once

#include "ITable.h"
#include "TVector.h"
#include <string>
#include <stdexcept>

enum class Status {
    empty,
    occupied,
    deleted
};

template<typename TVal>
struct HashData {
    std::string key;
    TVal val;
    Status state;

    HashData();
    HashData(const std::string& k, const TVal& v);
};

template<typename TVal>
class HashTableOA : public ITable<std::string, TVal> {
private:
    TVector<HashData<TVal>> _rows;
    size_t _size;
    size_t _shift;

    size_t h(const std::string& key) const;
    size_t hh(size_t hash) const;
    bool is_prime(size_t n) const;
    size_t next_prime(size_t n) const;
    void calculate_shift();
    void rehash();

public:
    HashTableOA();
    HashTableOA(size_t initial_capacity);
    ~HashTableOA() override;

    void insert(const std::string& key, const TVal& val) override;
    void erase(const std::string& key) override;
    TVal find(const std::string& key) const override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const std::string& key) const noexcept override;
    void replace(const std::string& key, const TVal& val) override;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    size_t get_shift() const noexcept;
};
template<typename TVal>
HashData<TVal>::HashData() : key(""), val(TVal()), state(Status::empty) {}

template<typename TVal>
HashData<TVal>::HashData(const std::string& k, const TVal& v)
    : key(k), val(v), state(Status::occupied) {}

template<typename TVal>
size_t HashTableOA<TVal>::h(const std::string& key) const {
    size_t hash = 0;
    for (char sym : key) {
        hash += sym;
    }
    return hash % _rows.getsize();
}

template<typename TVal>
size_t HashTableOA<TVal>::hh(size_t hash) const {
    return (hash + _shift) % _rows.getsize();
}

template<typename TVal>
bool HashTableOA<TVal>::is_prime(size_t n) const {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (size_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

template<typename TVal>
size_t HashTableOA<TVal>::next_prime(size_t n) const {
    while (!is_prime(n)) {
        n++;
    }
    return n;
}

template<typename TVal>
void HashTableOA<TVal>::calculate_shift() {
    size_t size = _rows.getsize();
    _shift = 1 + (size / 10);
    if (_shift < 1) _shift = 1;

    while (size % _shift == 0) {
        _shift++;
    }
}

template<typename TVal>
void HashTableOA<TVal>::rehash() {
    size_t new_size = next_prime(_rows.getsize() * 2);
    TVector<HashData<TVal>> old_rows = _rows;

    _rows = TVector<HashData<TVal>>(new_size);
    for (size_t i = 0; i < _rows.getsize(); i++) {
        _rows[i] = HashData<TVal>();
    }
    calculate_shift();
    _size = 0;

    for (size_t i = 0; i < old_rows.getsize(); i++) {
        if (old_rows[i].state == Status::occupied) {
            insert(old_rows[i].key, old_rows[i].val);
        }
    }
}

template<typename TVal>
HashTableOA<TVal>::HashTableOA() : _rows(next_prime(16)), _size(0) {
    for (size_t i = 0; i < _rows.getsize(); i++) {
        _rows[i] = HashData<TVal>();
    }
    calculate_shift();
}

template<typename TVal>
HashTableOA<TVal>::HashTableOA(size_t initial_capacity)
    : _rows(next_prime(initial_capacity)), _size(0) {
    for (size_t i = 0; i < _rows.getsize(); i++) {
        _rows[i] = HashData<TVal>();
    }
    calculate_shift();
}

template<typename TVal>
HashTableOA<TVal>::~HashTableOA() = default;

template<typename TVal>
void HashTableOA<TVal>::insert(const std::string& key, const TVal& val) {
    if (_size >= _rows.getsize() * 0.7) {
        rehash();
    }

    size_t hash = h(key);

    while (true) {
        if (_rows[hash].state != Status::occupied) {
            _rows[hash] = HashData<TVal>(key, val);
            _size++;
            return;
        }

        if (_rows[hash].key == key) {
            throw std::logic_error("Key already exists: " + key);
        }

        hash = hh(hash);
    }
}

template<typename TVal>
void HashTableOA<TVal>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t start_hash = hash;

    while (_rows[hash].state != Status::empty) {
        if (_rows[hash].state == Status::occupied && _rows[hash].key == key) {
            _rows[hash].state = Status::deleted;
            _size--;
            return;
        }

        hash = hh(hash);

        if (hash == start_hash) {
            return;
        }
    }

    throw std::logic_error("Key not found for erasure: " + key);
}

template<typename TVal>
TVal HashTableOA<TVal>::find(const std::string& key) const {
    size_t hash = h(key);
    size_t start_hash = hash;

    while (_rows[hash].state != Status::empty) {
        if (_rows[hash].state == Status::occupied && _rows[hash].key == key) {
            return _rows[hash].val;
        }

        hash = hh(hash);

        if (hash == start_hash) {
            break;
        }
    }

    throw std::logic_error("Key not found: " + key);
}

template<typename TVal>
std::ostream& HashTableOA<TVal>::print(std::ostream& out) const noexcept {
    out << "HashTableOA (Double Hashing)\n";
    out << "Capacity: " << _rows.getsize() << ", Size: " << _size << ", Shift: " << _shift << "\n";
    out << "----------------------------------------\n";

    for (size_t i = 0; i < _rows.getsize(); i++) {
        out << "[" << i << "] ";
        if (_rows[i].state == Status::occupied) {
            out << _rows[i].key << " : " << _rows[i].val;
        }
        else if (_rows[i].state == Status::deleted) {
            out << "DELETED";
        }
        else {
            out << "EMPTY";
        }
        out << "\n";
    }

    return out;
}

template<typename TVal>
bool HashTableOA<TVal>::is_empty() const noexcept {
    return _size == 0;
}

template<typename TVal>
bool HashTableOA<TVal>::consist(const std::string& key) const noexcept {
    try {
        find(key);
        return true;
    }
    catch (...) {
        return false;
    }
}

template<typename TVal>
void HashTableOA<TVal>::replace(const std::string& key, const TVal& val) {
    size_t hash = h(key);
    size_t start_hash = hash;

    while (_rows[hash].state != Status::empty) {
        if (_rows[hash].state == Status::occupied && _rows[hash].key == key) {
            _rows[hash].val = val;
            return;
        }

        hash = hh(hash);

        if (hash == start_hash) {
            break;
        }
    }
    throw std::logic_error("Key not found for replacement: " + key);
}

template<typename TVal>
size_t HashTableOA<TVal>::size() const noexcept {
    return _size;
}

template<typename TVal>
size_t HashTableOA<TVal>::capacity() const noexcept {
    return _rows.getsize();
}

template<typename TVal>
size_t HashTableOA<TVal>::get_shift() const noexcept {
    return _shift;
}