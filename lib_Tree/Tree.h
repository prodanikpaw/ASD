#pragma once
#include <iostream>
#include <cmath>
#include "queue.h"
#include "stack.h"
#include "TVector.h"

template<typename TKey, typename TValue>
struct Node {
    std::pair<TKey, TValue> data;
    Node* left;
    Node* right;

    Node(const TKey& key, const TValue& val);
};

template<typename TKey, typename TValue>
class Tree {
private:
    Node<TKey, TValue>* root;
    int count;

    void clearRecursive(Node<TKey, TValue>* node);
    Node<TKey, TValue>* findLastNode(Node<TKey, TValue>*& parent);
    Node<TKey, TValue>* findNodeWithParent(const TKey& key, Node<TKey, TValue>*& parent);

    void print_D1_rec(Node<TKey, TValue>* cur);
    void print_D2_rec(Node<TKey, TValue>* cur);
    void print_D3_rec(Node<TKey, TValue>* cur);

public:
    Tree();
    ~Tree();

    void insert(const TKey& key, const TValue& val);
    void replace(const TKey& key, const TValue& val);
    bool erase(const TKey& key);
    TValue find(const TKey& key) const;

    void print_D1();
    void print_D2();
    void print_D3();
    void print_W();

    void printTree() const;
    bool consist(const TKey& key) const;
    int size() const;
    bool empty() const;
    void clear();
    Node<TKey, TValue>* getroot()const;
};

template<typename TKey, typename TValue>
Node<TKey, TValue>::Node(const TKey& key, const TValue& val)
    : data(key, val), left(nullptr), right(nullptr) {}

template<typename TKey, typename TValue>
Tree<TKey, TValue>::Tree() : root(nullptr), count(0) {}

template<typename TKey, typename TValue>
Tree<TKey, TValue>::~Tree() {
    clear();
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::clearRecursive(Node<TKey, TValue>* node) {
    if (!node) return;
    clearRecursive(node->left);
    clearRecursive(node->right);
    delete node;
}

template<typename TKey, typename TValue>
Node<TKey, TValue>* Tree<TKey, TValue>::findLastNode(Node<TKey, TValue>*& parent) {
    if (!root) return nullptr;

    queue<Node<TKey, TValue>*> q;
    q.push(root);
    Node<TKey, TValue>* last = nullptr;
    parent = nullptr;

    while (!q.is_empty()) {
        last = q.head();
        q.pop();

        if (last->left) {
            parent = last;
            q.push(last->left);
        }
        if (last->right) {
            parent = last;
            q.push(last->right);
        }
    }
    return last;
}

template<typename TKey, typename TValue>
Node<TKey, TValue>* Tree<TKey, TValue>::findNodeWithParent(const TKey& key, Node<TKey, TValue>*& parent) {
    if (!root) return nullptr;

    if (root->data.first == key) {
        parent = nullptr;
        return root;
    }

    queue<Node<TKey, TValue>*> q;
    q.push(root);

    while (!q.is_empty()) {
        Node<TKey, TValue>* current = q.head();
        q.pop();

        if (current->left && current->left->data.first == key) {
            parent = current;
            return current->left;
        }
        if (current->right && current->right->data.first == key) {
            parent = current;
            return current->right;
        }

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }

    return nullptr;
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& val) {

    Node<TKey, TValue>* tempParent = nullptr;
    Node<TKey, TValue>* existing = findNodeWithParent(key, tempParent);

    if (existing) {
        throw std::logic_error("Key already exists");
    }

    Node<TKey, TValue>* newNode = new Node<TKey, TValue>(key, val);

    if (!root) {
        root = newNode;
        count++;
        return;
    }

    queue<Node<TKey, TValue>*> q;
    q.push(root);

    while (!q.is_empty()) {
        Node<TKey, TValue>* current = q.head();
        q.pop();

        if (!current->left) {
            current->left = newNode;
            count++;
            return;
        }
        else if (!current->right) {
            current->right = newNode;
            count++;
            return;
        }

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::replace(const TKey& key, const TValue& val) {
    Node<TKey, TValue>* tempParent = nullptr;
    Node<TKey, TValue>* existing = findNodeWithParent(key, tempParent);

    if (!existing) {
        throw std::out_of_range("Key not found for replace");
    }

    existing->data.second = val;
}

template<typename TKey, typename TValue>
bool Tree<TKey, TValue>::erase(const TKey& key) {
    if (!root) return false;

    Node<TKey, TValue>* parent = nullptr;
    Node<TKey, TValue>* toDelete = findNodeWithParent(key, parent);

    if (!toDelete) return false;

    if (count == 1) {
        delete root;
        root = nullptr;
        count = 0;
        return true;
    }

    Node<TKey, TValue>* lastParent = nullptr;
    Node<TKey, TValue>* last = findLastNode(lastParent);

    if (last) {
        toDelete->data = last->data;

        if (lastParent) {
            if (lastParent->left == last) lastParent->left = nullptr;
            else lastParent->right = nullptr;
        }
        delete last;
        count--;
    }

    return true;
}

template<typename TKey, typename TValue>
TValue Tree<TKey, TValue>::find(const TKey& key) const {
    Node<TKey, TValue>* tempParent = nullptr;
    Node<TKey, TValue>* node = const_cast<Tree<TKey, TValue>*>(this)->findNodeWithParent(key, tempParent);

    if (!node) {
        throw std::out_of_range("Key not found");
    }
    return node->data.second;
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_D1_rec(Node<TKey, TValue>* cur) {
    if (cur == nullptr) {
        return;
    }
    std::cout << cur->data.first << ":" << cur->data.second << " ";
    print_D1_rec(cur->left);
    print_D1_rec(cur->right);
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_D2_rec(Node<TKey, TValue>* cur) {
    if (cur == nullptr) {
        return;
    }
    print_D2_rec(cur->left);
    std::cout << cur->data.first << ":" << cur->data.second << " ";
    print_D2_rec(cur->right);
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_D3_rec(Node<TKey, TValue>* cur) {
    if (cur == nullptr) {
        return;
    }
    print_D3_rec(cur->left);
    print_D3_rec(cur->right);
    std::cout << cur->data.first << ":" << cur->data.second << " ";
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_D1() {
    if (!root) {
        std::cout << "Дерево пусто";
        return;
    }
    print_D1_rec(root);
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_D2() {
    if (!root) {
        std::cout << "Дерево пусто";
        return;
    }
    print_D2_rec(root);
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_D3() {
    if (!root) {
        std::cout << "Дерево пусто";
        return;
    }
    print_D3_rec(root);
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_W() {
    if (!root) {
        std::cout << "tree is empty";
        return;
    }

    queue<Node<TKey, TValue>*> q;
    q.push(root);

    while (!q.is_empty()) {
        Node<TKey, TValue>* current = q.head();
        q.pop();

        std::cout << current->data.first << ":" << current->data.second << " ";

        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::printTree() const {
    if (!root) {
        std::cout << "tree is empty\n";
        return;
    }

    std::cout << "\n=== good print ===\n";

    struct NodeWithLevel {
        Node<TKey, TValue>* node;
        int level;
        int position;
    };

    queue<NodeWithLevel> q;
    q.push({ root, 0, 0 });

    int currentLevel = 0;
    TVector<TVector<std::pair<TKey, int>>> levels;
    levels.push_back(TVector<std::pair<TKey, int>>());

    while (!q.is_empty()) {
        NodeWithLevel nwl = q.head();
        q.pop();

        Node<TKey, TValue>* node = nwl.node;
        int level = nwl.level;
        int pos = nwl.position;

        if (level > currentLevel) {
            levels.push_back(TVector<std::pair<TKey, int>>());
            currentLevel = level;
        }

        levels[level].push_back({ node->data.first, pos });

        if (node->left) q.push({ node->left, level + 1, pos * 2 });
        if (node->right) q.push({ node->right, level + 1, pos * 2 + 1 });
    }

    for (int i = 0; i < levels.getsize(); i++) {
        int indent = std::pow(2, levels.getsize() - i - 1) - 1;
        std::cout << std::string(indent * 4, ' ');

        for (int j = 0; j < levels[i].getsize(); j++) {
            std::cout << levels[i][j].first;

            if (j < levels[i].getsize() - 1) {
                int gap = std::pow(2, levels.getsize() - i) * 4 - 4;
                std::cout << std::string(gap, ' ');
            }
        }
        std::cout << "\n";

        if (i < levels.getsize() - 1) {
            std::cout << std::string(indent * 4, ' ');
            for (int j = 0; j < levels[i].getsize(); j++) {
                std::cout << "/";
                int gap = std::pow(2, levels.getsize() - i) * 4 - 6;
                if (j < levels[i].getsize() - 1) {
                    std::cout << std::string(gap, ' ') << "\\";
                    std::cout << std::string(4, ' ');
                }
            }
            std::cout << "\n";
        }
    }

    std::cout << "===========================\n\n";
}

template<typename TKey, typename TValue>
bool Tree<TKey, TValue>::consist(const TKey& key) const {
    Node<TKey, TValue>* tempParent = nullptr;
    return const_cast<Tree<TKey, TValue>*>(this)->findNodeWithParent(key, tempParent) != nullptr;
}

template<typename TKey, typename TValue>
int Tree<TKey, TValue>::size() const {
    return count;
}

template<typename TKey, typename TValue>
bool Tree<TKey, TValue>::empty() const {
    return count == 0;
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::clear() {
    clearRecursive(root);
    root = nullptr;
    count = 0;
}

template<typename TKey, typename TValue>
Node<TKey, TValue>* Tree<TKey, TValue>::getroot()const {
    return root;
}
