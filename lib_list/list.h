#include <stdexcept>

template <class T>
struct Node {
    T value;
    Node<T>* next;

    Node(T val, Node<T>* nxt = nullptr) : value(val), next(nxt) {}
};

template <class T>
class List {
    Node<T>* _head;
    Node<T>* _tail;
    int _count;

public:
    List();
    List(const List<T>& other);
    ~List();

    List<T>& operator=(const List<T>& other);

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(int pos, const T& val);
    void insert(Node<T>* node, const T& val);

    void pop_front();
    void pop_back();
    void pop(int pos);
    void pop(Node<T>* node);

    bool is_empty()const;
    Node<T>* find(const T& val);
    int size() const;

    class Iterator {
        Node<T>* current;
    public:
        Iterator() : current(nullptr) {};
        Iterator(Node<T>* pos) : current(pos) {};
        Iterator(const Iterator& other) : current(other.current) {};

        Iterator& operator=(const Iterator& other) {
            if (this != &other) { current = other.current; }
            return *this;
        }

        T& operator*() {
            if (current == nullptr) {
                throw std::logic_error("Dereferencing null iterator");
            }
            return current->value;
        }

        const T& operator*() const {
            if (current == nullptr) {
                throw std::logic_error("Dereferencing null iterator");
            }
            return current->value;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        Node<T>* get_current() const { return current; }
    };

    Iterator begin() { return Iterator (_head); }
    Iterator end() { return Iterator (nullptr); }
    Iterator  begin() const { return Iterator (_head); }
    Iterator  end() const { return Iterator (nullptr); }
};

template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr), _count(0) {}

template <class T>
List<T>::List(const List<T>& other) {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;

    Node<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <class T>
List<T>::~List() {
    while (!is_empty()) {
        pop_front();
    }
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        while (!is_empty()) {
            pop_front();
        }

        Node<T>* current = other._head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}

template <class T>
void List<T>::push_front(const T& val) noexcept {
    Node<T>* newNode = new Node<T>(val, _head);

    if (_head == nullptr) {
        _head = _tail = newNode;
    }
    else {
        _head = newNode;
    }
    _count++;
}

template <class T>
void List<T>::push_back(const T& val) noexcept {
    Node<T>* newNode = new Node<T>(val);

    if (_tail == nullptr) {
        _head = _tail = newNode;
    }
    else {
        _tail->next = newNode;
        _tail = newNode;
    }
    _count++;
}

template <class T>
void List<T>::insert(int pos, const T& val) {
    if (pos < 0 || pos > _count) {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0) {
        push_front(val);
    }
    else if (pos == _count) {
        push_back(val);
    }
    else {
        Node<T>* current = _head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }

        Node<T>* newNode = new Node<T>(val, current->next);
        current->next = newNode;
        _count++;
    }
}

template <class T>
void List<T>::insert(Node<T>* node, const T& val) {
    if (node == nullptr) {
        push_back(val);
        return;
    }

    if (node == _head) {
        push_front(val);
    }
    else {
        Node<T>* prev = _head;
        while (prev != nullptr && prev->next != node) {
            prev = prev->next;
        }

        if (prev != nullptr) {
            Node<T>* newNode = new Node<T>(val, node);
            prev->next = newNode;
            _count++;
        }
    }
}

template <class T>
void List<T>::pop_front() {
    if (_head == nullptr) return;

    Node<T>* temp = _head;
    _head = _head->next;

    if (_head == nullptr) {
        _tail = nullptr;
    }

    delete temp;
    _count--;
}

template <class T>
void List<T>::pop_back() {
    if (_tail == nullptr) return;

    if (_head == _tail) {
        delete _head;
        _head = _tail = nullptr;
    }
    else {
        Node<T>* current = _head;
        while (current->next != _tail) {
            current = current->next;
        }

        delete _tail;
        current->next = nullptr;
        _tail = current;
    }
    _count--;
}

template <class T>
void List<T>::pop(int pos) {
    if (pos < 0 || pos >= _count) {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0) {
        pop_front();
    }
    else if (pos == _count - 1) {
        pop_back();
    }
    else {
        Node<T>* current = _head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }

        Node<T>* temp = current->next;
        current->next = temp->next;

        if (temp == _tail) {
            _tail = current;
        }

        delete temp;
        _count--;
    }
}

template <class T>
void List<T>::pop(Node<T>* node) {
    if (node == nullptr) return;

    if (node == _head) {
        pop_front();
    }
    else {
        Node<T>* current = _head;
        while (current != nullptr && current->next != node) {
            current = current->next;
        }

        if (current != nullptr) {
            current->next = node->next;

            if (node == _tail) {
                _tail = current;
            }

            delete node;
            _count--;
        }
    }
}

template <class T>
bool List<T>::is_empty()const {
    return _head == nullptr;
}

template <class T>
Node<T>* List<T>::find(const T& val) {
    Node<T>* current = _head;
    while (current != nullptr) {
        if (current->value == val) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <class T>
int List<T>::size() const {
    return _count;
}