

#include <gtest/gtest.h>
#include "../lib_easy_example/easy_example.h"
#include "../lib_stack/stack.h"

TEST(StackTest, is_empty_on_creation) {

    stack<int> s;


    ASSERT_TRUE(s.is_empty());
    ASSERT_FALSE(s.is_full());
}

TEST(StackTest, push_and_top_operations) {

    stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);


    ASSERT_EQ(s.top(), 30);
    ASSERT_FALSE(s.is_empty());
}

TEST(StackTest, pop_operations) {

    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    ASSERT_EQ(s.top(), 30);
    s.pop();
    ASSERT_EQ(s.top(), 20);
    s.pop();
    ASSERT_EQ(s.top(), 10);
    s.pop();
    ASSERT_TRUE(s.is_empty());
}

TEST(StackTest, clear_operation) {

    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);


    s.clear();


    ASSERT_TRUE(s.is_empty());
}

TEST(StackTest, throw_when_pop_empty_stack) {
    stack<int> s;

    ASSERT_THROW(s.pop(), std::logic_error);
}

TEST(StackTest, throw_when_top_empty_stack) {

    stack<int> s;

    ASSERT_THROW(s.top(), std::logic_error);
}

TEST(StackTest, push_after_clear) {
    stack<int> s;
    s.push(10);
    s.push(20);
    s.clear();

    s.push(40);

    ASSERT_EQ(s.top(), 40);
    ASSERT_FALSE(s.is_empty());
}

TEST(StackTest, works_with_string_type) {
    stack<std::string> s;

    s.push("hello");
    s.push("world");

    ASSERT_EQ(s.top(), "world");
    s.pop();
    ASSERT_EQ(s.top(), "hello");
}

TEST(StackTest, multiple_push_pop_operations) {
    stack<int> s;

    for (int i = 0; i < 50; ++i) {
        s.push(i);
        ASSERT_EQ(s.top(), i);
    }

    for (int i = 49; i >= 0; --i) {
        ASSERT_EQ(s.top(), i);
        s.pop();
    }

    ASSERT_TRUE(s.is_empty());
}

TEST(StackTest, is_full_detection) {
    stack<int> s;

    for (int i = 0; i < 100; ++i) {
        s.push(i);
    }

    ASSERT_TRUE(s.is_full());
}

TEST(StackTest, throw_when_push_full_stack) {

    stack<int> s;

    for (int i = 0; i < 100; ++i) {
        s.push(i);
    }

    ASSERT_THROW(s.push(101), std::logic_error);
}