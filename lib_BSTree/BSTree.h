#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

template<typename TKey, typename TValue>
class BSTree {
private:
    struct Node {
        std::pair<TKey, TValue> data;
        Node* left;
        Node* right;

        Node(const TKey& key, const TValue& val)
            : data(key, val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* find_pos(const TKey& key) const noexcept;
    void clear_rec(Node* node) noexcept;
    Node* copy_rec(Node* node);
    void to_string_rec(Node* node, std::string& result) const noexcept;
    void to_string_sorted_rec(Node* node, std::string& result) const noexcept;

public:
    BSTree() noexcept;
    BSTree(const BSTree& other);
    ~BSTree();

    BSTree& operator=(const BSTree& other);

    void insert(const TKey& key, const TValue& val);
    TValue find(const TKey& key) const;
    void erase(const TKey& key);
    void replace(const TKey& key, const TValue& val);
    bool consist(const TKey& key) const noexcept;
    bool isEmpty() const noexcept;
    std::string to_string() const noexcept;
    std::string to_string_sorted() const noexcept;
};


template<typename TKey, typename TValue>
BSTree<TKey, TValue>::BSTree() noexcept : root(nullptr) {}

template<typename TKey, typename TValue>
BSTree<TKey, TValue>::BSTree(const BSTree& other) : root(nullptr) {
    if (other.root) {
        root = copy_rec(other.root);
    }
}

template<typename TKey, typename TValue>
BSTree<TKey, TValue>::~BSTree() {
    clear_rec(root);
}

template<typename TKey, typename TValue>
BSTree<TKey, TValue>& BSTree<TKey, TValue>::operator=(const BSTree& other) {
    if (this != &other) {
        clear_rec(root);
        root = copy_rec(other.root);
    }
    return *this;
}

template<typename TKey, typename TValue>
typename BSTree<TKey, TValue>::Node*
BSTree<TKey, TValue>::copy_rec(Node* node) {
    if (!node) return nullptr;
    Node* new_node = new Node(node->data.first, node->data.second);
    new_node->left = copy_rec(node->left);
    new_node->right = copy_rec(node->right);
    return new_node;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::clear_rec(Node* node) noexcept {
    if (node) {
        clear_rec(node->left);
        clear_rec(node->right);
        delete node;
    }
}

template<typename TKey, typename TValue>
typename BSTree<TKey, TValue>::Node*
BSTree<TKey, TValue>::find_pos(const TKey& key) const noexcept {
    Node* cur = root;
    Node* prev = nullptr;

    while (cur != nullptr && cur->data.first != key) {
        prev = cur;
        if (cur->data.first > key) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }

    if (cur != nullptr) {
        return cur;
    }
    else {
        return prev;
    }
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    Node* found = find_pos(key);

    if (isEmpty()) {
        root = new Node(key, val);
        return;
    }

    if (found && found->data.first == key) {
        throw std::logic_error("Key already exists");
    }

    Node* new_node = new Node(key, val);
    if (found->data.first > key) {
        found->left = new_node;
    }
    else {
        found->right = new_node;
    }
}

template<typename TKey, typename TValue>
TValue BSTree<TKey, TValue>::find(const TKey& key) const {
    if (isEmpty()) {
        throw std::logic_error("Tree is empty");
    }

    Node* found = find_pos(key);
    if (found == nullptr || found->data.first != key) {
        throw std::logic_error("Key not found");
    }

    return found->data.second;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    if (isEmpty()) {
        throw std::logic_error("Tree is empty");
    }

    Node* parent = nullptr;
    Node* to_del = root;

    while (to_del != nullptr && to_del->data.first != key) {
        parent = to_del;
        if (to_del->data.first > key) {
            to_del = to_del->left;
        }
        else {
            to_del = to_del->right;
        }
    }

    if (to_del == nullptr) {
        throw std::logic_error("Key not found");
    }

    if (to_del->left == nullptr || to_del->right == nullptr) {
        Node* rep = nullptr;
        if (to_del->left == nullptr && to_del->right == nullptr) {
            rep = nullptr;
        }
        else if (to_del->left == nullptr) { // dublicate!!!!!
            rep = to_del->right;
        }
        else if (to_del->right == nullptr) {
            rep = to_del->left;
        }

        if (parent == nullptr) {
            root = rep;
        }
        else if (parent->left == to_del) {
            parent->left = rep;
        }
        else {
            parent->right = rep;
        }
        delete to_del;


        //if (to_del->left == nullptr && to_del->right == nullptr) {
        //    if (parent == nullptr) {
        //        root = nullptr;
        //    }
        //    else if (parent->left == to_del) {
        //        parent->left = nullptr;
        //    }
        //    else {
        //        parent->right = nullptr;
        //    }
        //    delete to_del;
        //}

        //else if (to_del->left == nullptr) { // dublicate!!!!!
        //    if (parent == nullptr) {
        //        root = to_del->right;
        //    }
        //    else if (parent->left == to_del) {
        //        parent->left = to_del->right;
        //    }
        //    else {
        //        parent->right = to_del->right;
        //    }
        //    delete to_del;
        //}

        //else if (to_del->right == nullptr) {
        //    if (parent == nullptr) {
        //        root = to_del->left;
        //    }
        //    else if (parent->left == to_del) {
        //        parent->left = to_del->left;
        //    }
        //    else {
        //        parent->right = to_del->left;
        //    }
        //    delete to_del;
        //}

    }
    else {
        Node* max_parent = to_del;
        Node* max_node = to_del->left;

        while (max_node->right != nullptr) {
            max_parent = max_node;
            max_node = max_node->right;
        }

        to_del->data = max_node->data;

        if (max_parent->left == max_node) {
            max_parent->left = max_node->left;
        }
        else {
            max_parent->right = max_node->left;
        }
        delete max_node;
    }
}


template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::replace(const TKey& key, const TValue& val) {
    if (isEmpty()) {
        throw std::logic_error("Tree is empty");
    }

    Node* found = find_pos(key);

    if (found == nullptr || found->data.first != key) {
        throw std::logic_error("Key not found");
    }

    found->data.second = val;
}

template<typename TKey, typename TValue>
bool BSTree<TKey, TValue>::consist(const TKey& key) const noexcept {
    if (isEmpty()) {
        return false;
    }

    Node* found = find_pos(key);

    if (found == nullptr || found->data.first != key) {
        return false;
    }

    return true;
}

template<typename TKey, typename TValue>
bool BSTree<TKey, TValue>::isEmpty() const noexcept {
    return root == nullptr;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::to_string_rec(Node* node, std::string& result) const noexcept {
    if (!node) return;

    std::ostringstream oss;
    oss << "(" << node->data.first << ":" << node->data.second << ")";
    result += oss.str();

    if (node->left || node->right) {
        result += "[";
        size_t old_size = result.size();
        to_string_rec(node->left, result);
        if (result.size() > old_size && node->right) {
            result += ",";
        }

        to_string_rec(node->right, result);
        result += "]";
    }
}

template<typename TKey, typename TValue>
std::string BSTree<TKey, TValue>::to_string() const noexcept {
    if (isEmpty()) return "[]";
    std::string result;
    to_string_rec(root, result);
    return "[" + result + "]";
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::to_string_sorted_rec(Node* node, std::string& result) const noexcept {
    if (!node) return;

    to_string_sorted_rec(node->left, result);

    std::ostringstream oss;
    oss << "(" << node->data.first << ":" << node->data.second << ")";

    if (!result.empty()) {
        result += "," + oss.str();
    }
    else {
        result += oss.str();
    }

    to_string_sorted_rec(node->right, result);
}

template<typename TKey, typename TValue>
std::string BSTree<TKey, TValue>::to_string_sorted() const noexcept {
    if (isEmpty()) return "[]";
    std::string result;
    to_string_sorted_rec(root, result);
    return "[" + result + "]";
}