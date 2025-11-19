#pragma once

#include "stack.h"
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