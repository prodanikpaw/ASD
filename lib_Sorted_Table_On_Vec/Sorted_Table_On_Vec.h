#include "ITable.h"
#include "TVector.h"
#include <iostream>

template<typename TKey, typename TValue>
class Sorted_Table_On_Vec : public ITable<TKey, TValue> {
    TVector<std::pair<TKey, TValue>> _rows;

    
    int find_position(const TKey& key) const;
    int find_insert_position(const TKey& key) const;

public:
    Sorted_Table_On_Vec() = default;
    ~Sorted_Table_On_Vec() = default;

    TValue find(const TKey& key) const override;
    void insert(const TKey& key, const TValue& val) override;
    void erase(const TKey& key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& key) const noexcept override;
    void replace(const TKey& key, const TValue& val) override;

    int size() const noexcept;
    void clear();
};

//бинарный
template<typename TKey, typename TValue>
int Sorted_Table_On_Vec<TKey, TValue>::find_position(const TKey& key) const {
    int left = 0;
    int right = _rows.getsize() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (_rows[mid].first == key) {
            return mid;
        }
        else if (_rows[mid].first < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// Поиск позиции для вставки нового элемента 
template<typename TKey, typename TValue>
int Sorted_Table_On_Vec<TKey, TValue>::find_insert_position(const TKey& key) const {
    int left = 0;
    int right = _rows.getsize() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (_rows[mid].first < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return left;
}


template<typename TKey, typename TValue>
TValue Sorted_Table_On_Vec<TKey, TValue>::find(const TKey& key) const {
    int pos = find_position(key);
    if (pos != -1) {
        return _rows[pos].second;
    }
    return TValue();
}

template<typename TKey, typename TValue>
void Sorted_Table_On_Vec<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    int pos = find_position(key);

    if (pos != -1) {
        throw std::invalid_argument("Key already exists in the table");
    }

    int insert_pos = find_insert_position(key);

    _rows.insert(insert_pos, std::make_pair(key, val));
}


template<typename TKey, typename TValue>
void Sorted_Table_On_Vec<TKey, TValue>::erase(const TKey& key) {
    int pos = find_position(key);
    if (pos != -1) {
        _rows.erase(pos);
    }
}


template<typename TKey, typename TValue>
std::ostream& Sorted_Table_On_Vec<TKey, TValue>::print(std::ostream& out) const noexcept {
    out << "Sorted Table Contents (sorted by key):" << std::endl;
    out << "========================================" << std::endl;

    if (_rows.getsize() == 0) {
        out << "Table is empty" << std::endl;
    }
    else {
        for (int i = 0; i < _rows.getsize(); ++i) {
            out << "  [" << i << "] " << _rows[i].first
                << " -> " << _rows[i].second << std::endl;
        }
    }

    out << "========================================" << std::endl;
    out << "Total elements: " << _rows.getsize() << std::endl;

    return out;
}

template<typename TKey, typename TValue>
bool Sorted_Table_On_Vec<TKey, TValue>::is_empty() const noexcept {
    return _rows.getsize() == 0;
}

template<typename TKey, typename TValue>
bool Sorted_Table_On_Vec<TKey, TValue>::consist(const TKey& key) const noexcept {
    return find_position(key) != -1;
}

template<typename TKey, typename TValue>
void Sorted_Table_On_Vec<TKey, TValue>::replace(const TKey& key, const TValue& val) {
    int pos = find_position(key);
    if (pos != -1) {
        _rows[pos].second = val;
    }
}

template<typename TKey, typename TValue>
int Sorted_Table_On_Vec<TKey, TValue>::size() const noexcept {
    return _rows.getsize();
}

template<typename TKey, typename TValue>
void Sorted_Table_On_Vec<TKey, TValue>::clear() {
    while (_rows.getsize() > 0) {
        _rows.pop_back();
    }
}