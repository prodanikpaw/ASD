#pragma once

#include "stack.h"
#include "list.h"
bool check_breckets(const std::string& stk);

bool check_breckets(const std::string& stk) {
    stack<char> brackets;
    for (auto b : stk) {
        if (b == '(' || b == '{' || b == '[') {
            brackets.push(b);
        }
        else if (b == ')' || b == '}' || b == ']') {
            if (brackets.is_empty()) {
                return false;
            }
            char top = brackets.top();
            brackets.pop();
            if ((b == ')' && top != '(') || (b == '}' && top != '{') || (b == ']' && top != '[')) {
                return false;
            }
        }
    }
    return brackets.is_empty();
}

template <class T>
bool has_cycle(const List<T>& list) {

    if (list.is_empty() || list.size() == 1) {
        return false;
    }


    auto tortoise = list.begin();
    auto hare = list.begin();

    
    if (hare != list.end()) {
        ++hare;
    }

    while (hare != list.end() && tortoise != list.end()) {
       
        if (tortoise.get_current() == hare.get_current()) {
            return true;
        }

        ++tortoise;

        if (hare != list.end()) {
            ++hare;
            if (hare != list.end()) {
                ++hare;
            }
        }
    }
    return false;
}


template <class T>
bool has_cycle_reverse(List<T>& list) {
    if (list.is_empty() || list.size() == 1) {
        return false;
    }

    Node<T>* head = list.begin().get_current();
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    Node<T>* next = nullptr;

    
    bool has_cycle = false;
    int count = 0;
    int list_size = list.size();

    while (current != nullptr && count <= list_size + 1) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;

        if (current == head) {
            has_cycle = true;
            break;
        }
    }

    Node<T>* new_head = prev;
    current = new_head;
    prev = nullptr;

    
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;

        
        if (prev == head) {
            break;
        }
    }

    return has_cycle;
}

template <class T>
Node<T>* find_cycle_node(const List<T>& list)
{
    
    if (list.is_empty()) {
        return nullptr;
    }

    // Получаем указатель на голову напрямую
    Node<T>* head = list.begin().get_current();
    if (head == nullptr) {
        return nullptr;
    }

     
    Node<T>* slow = head;
    Node<T>* fast = head;

    
    bool has_cycle = false;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            has_cycle = true;
            break;
        }
    }

    if (!has_cycle) {
        return nullptr;
    }

    // Фаза 2: Находим начало цикла
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}



