#pragma once
#include <iostream>
#include "list.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

template<typename TKey, typename TValue>
struct SkipNode {
	std::pair<TKey, TValue> data;
	SkipNode<TKey, TValue>** next;
	size_t level;

	SkipNode(const TKey& key, const TValue& value, size_t lvl) : data(key, value), level(lvl) {
		next = new SkipNode<TKey, TValue>* [level + 1];
		for (size_t i = 0; i <= level; ++i) {
			next[i] = nullptr;
		}
	}

	~SkipNode() {
		delete[] next;
	}
};


template<typename TKey, typename TValue>
class SkipList {
private:
    List<SkipNode<TKey, TValue>*> _heads;
    size_t _cur_level;
    size_t _max_level;

    SkipNode<TKey, TValue>* getHeadAtLevel(size_t level);
    void setHeadAtLevel(size_t level, SkipNode<TKey, TValue>* node);

	size_t generateLevel();


public:
    SkipList(size_t max_level = 10);
    ~SkipList();

    List<SkipNode<TKey, TValue>*> findPath(const TKey& key);

	void insert(const TKey& key, const TValue& value);
    void insert(const TKey& key, const TValue& value, size_t level);
    SkipNode<TKey, TValue>* find(const TKey& key);

    void print();

    size_t getCurrentLevel() const;
    size_t getMaxLevel() const;

};


template<typename TKey, typename TValue>
SkipList<TKey, TValue>::SkipList(size_t max_level)
    : _cur_level(0), _max_level(max_level) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (size_t i = 0; i <= _max_level; ++i) {
        _heads.push_back(nullptr);
    }
}

template<typename TKey, typename TValue>
SkipList<TKey, TValue>::~SkipList() {
    SkipNode<TKey, TValue>* current = getHeadAtLevel(0);
    while (current != nullptr) {
        SkipNode<TKey, TValue>* next = current->next[0];
        delete current;
        current = next;
    }
}

template<typename TKey, typename TValue>
SkipNode<TKey, TValue>* SkipList<TKey, TValue>::getHeadAtLevel(size_t level) {
    if (level >= _heads.size()) return nullptr;

    auto it = _heads.begin();
    for (size_t i = 0; i < level; ++i) {
        ++it;
    }
    return *it;
}

template<typename TKey, typename TValue>
void SkipList<TKey, TValue>::setHeadAtLevel(size_t level, SkipNode<TKey, TValue>* node) {
    while (_heads.size() <= level) {
        _heads.push_back(nullptr);
    }

    auto it = _heads.begin();
    for (size_t i = 0; i < level; ++i) {
        ++it;
    }
    *it = node;
}

template<typename TKey, typename TValue>
size_t SkipList<TKey, TValue>::generateLevel() {
    size_t level = 0;
    while (level < _max_level) {
        if ((std::rand() % 100) < 50) {
            level++;
        }
        else {
            break;
        }
    }

    return level;
}

template<typename TKey, typename TValue>
List<SkipNode<TKey, TValue>*> SkipList<TKey, TValue>::findPath(const TKey& key) {
    List<SkipNode<TKey, TValue>*> path;
    for (size_t i = 0; i <= _max_level; ++i) {
        path.push_back(nullptr);
    }

    SkipNode<TKey, TValue>* current = nullptr;
    for (int i = _cur_level; i >= 0; --i) {
        if (i < _cur_level) {
            auto it = path.begin();
            for (int j = 0; j < i + 1; ++j) ++it;
            current = *it;
        }

        if (current == nullptr) {
            current = getHeadAtLevel(i);
        }
        else {
            current = current->next[i];
        }

        while (current != nullptr && current->next[i] != nullptr &&
            current->next[i]->data.first < key) {
            current = current->next[i];
        }

        auto it = path.begin();
        for (int j = 0; j < i; ++j) ++it;

        if (current != nullptr && current->data.first < key) {
            *it = current;
        }
        else {
            if (i < _cur_level) {
                auto itNext = path.begin();
                for (int j = 0; j < i + 1; ++j) ++itNext;
                *it = *itNext;
            }
            else {
                *it = nullptr;
            }
        }
    }

    return path;
}


template<typename TKey, typename TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    size_t new_level = generateLevel();
    insert(key, value, new_level);
}

template<typename TKey, typename TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value, size_t level) {
    List<SkipNode<TKey, TValue>*> path = findPath(key);

    auto it0 = path.begin();
    SkipNode<TKey, TValue>* prev0 = *it0;
    SkipNode<TKey, TValue>* next;
    if (prev0 != nullptr) {
        next = prev0->next[0];
    }
    else {
        next = getHeadAtLevel(0);
    }

    if (next != nullptr && next->data.first == key) {
        next->data.second = value;
        return;
    }

    if (level > _cur_level) {
        auto it = path.begin();
        for (size_t i = 0; i <= level; ++i) {
            if (i > _cur_level) {
                *it = nullptr;
            }
            ++it;
        }
        _cur_level = level;
    }
    SkipNode<TKey, TValue>* new_node = new SkipNode<TKey, TValue>(key, value, level);

    // Вставляем узел на всех уровнях от 0 до level
    auto it = path.begin();
    for (size_t i = 0; i <= level; ++i) {
        SkipNode<TKey, TValue>* prev = *it;

        if (prev != nullptr) {
            new_node->next[i] = prev->next[i];
            prev->next[i] = new_node;
        }
        else {
            new_node->next[i] = getHeadAtLevel(i);
            setHeadAtLevel(i, new_node);
        }

        ++it;
    }
}

template<typename TKey, typename TValue>
size_t SkipList<TKey, TValue>::getCurrentLevel() const {
    return _cur_level;
}

template<typename TKey, typename TValue>
size_t SkipList<TKey, TValue>::getMaxLevel() const {
    return _max_level;
}


template<typename TKey, typename TValue>
SkipNode<TKey, TValue>* SkipList<TKey, TValue>::find(const TKey& key) {
    List<SkipNode<TKey, TValue>*> path = findPath(key);

    auto it0 = path.begin();
    SkipNode<TKey, TValue>* prev0 = *it0;
    SkipNode<TKey, TValue>* current;
    if (prev0 != nullptr) {
        current = prev0->next[0];
    }
    else {
        current = getHeadAtLevel(0);
    }
    if (current != nullptr && current->data.first == key) {
        return current;
    }
    return nullptr;
}

template<typename TKey, typename TValue>
void SkipList<TKey, TValue>::print() {
    SkipNode<TKey, TValue>* current = getHeadAtLevel(0);

    while (current != nullptr) {
        std::cout << "(";

        std::cout << std::left << std::setw(12) << current->data.first;

        std::cout << " : ";

        std::cout << std::left << std::setw(12) << current->data.second;

        std::cout << ") ";

        for (size_t i = 0; i <= current->level; ++i) {
            std::cout << "[ ] ";
        }

        std::cout << std::endl;
        current = current->next[0];
    }
}
