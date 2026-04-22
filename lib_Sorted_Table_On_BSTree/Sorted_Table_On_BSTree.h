#pragma once
#include"BSTree.h"
#include"ITable.h"


template<typename TKey, typename TValue>
class SortedBSTreeTable : public ITable<TKey, TValue> {
private:
    BSTree<TKey, TValue> _tree;

public:
    SortedBSTreeTable() = default;
    ~SortedBSTreeTable() = default;
    SortedBSTreeTable(const SortedBSTreeTable& other) : _tree(other._tree) {}

    SortedBSTreeTable& operator=(const SortedBSTreeTable& other) {
        if (this != &other) {
            _tree = other._tree;
        }
        return *this;
    }

    void insert(const TKey& key, const TValue& val) override {
        try {
            _tree.insert(key, val);
        }
        catch (const std::logic_error&) {
        }
    }

    void erase(const TKey& key) override {
        try {
            _tree.erase(key);
        }
        catch (const std::logic_error& e) {
            throw std::out_of_range(e.what());
        }
    }

    TValue find(const TKey& key) const override {
        try {
            return _tree.find(key);
        }
        catch (const std::logic_error& e) {
            throw std::out_of_range(e.what());
        }
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        out << _tree.to_string_sorted();
        return out;
    }

    bool is_empty() const noexcept override {
        return _tree.isEmpty();
    }

    bool consist(const TKey& key) const noexcept override {
        return _tree.consist(key);
    }

    void replace(const TKey& key, const TValue& val) override {
        try {
            _tree.replace(key, val);
        }
        catch (const std::logic_error& e) {
            throw std::out_of_range(e.what());
        }
    }
};