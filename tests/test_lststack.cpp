#include <gtest/gtest.h>
#include "Lststack.h"

TEST(LstStackTest, is_empty_on_creation) {

    lststack<int> s;

    ASSERT_TRUE(s.is_empty());
}

TEST(LstStackTest, push_and_top_operations) {

    lststack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    ASSERT_EQ(s.top(), 30);
    ASSERT_FALSE(s.is_empty());
}

TEST(LstStackTest, pop_operations) {

    lststack<int> s;
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

TEST(LstStackTest, clear_operation) {

    lststack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    s.clear();

    ASSERT_TRUE(s.is_empty());
}

TEST(LstStackTest, throw_when_pop_empty_stack) {
    lststack<int> s;

    ASSERT_THROW(s.pop(), std::logic_error);
}

TEST(LstStackTest, throw_when_top_empty_stack) {

    lststack<int> s;

    ASSERT_THROW(s.top(), std::logic_error);
}

TEST(LstStackTest, push_after_clear) {
    lststack<int> s;
    s.push(10);
    s.push(20);
    s.clear();

    s.push(40);

    ASSERT_EQ(s.top(), 40);
    ASSERT_FALSE(s.is_empty());
}

TEST(LstStackTest, works_with_string_type) {
    lststack<std::string> s;

    s.push("hello");
    s.push("world");

    ASSERT_EQ(s.top(), "world");
    s.pop();
    ASSERT_EQ(s.top(), "hello");
}

TEST(LstStackTest, multiple_push_pop_operations) {
    lststack<int> s;

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

TEST(LstStackTest, large_number_of_elements) {
    lststack<int> s;

    for (int i = 0; i < 1000; ++i) {
        s.push(i);
        ASSERT_EQ(s.top(), i);
    }

    for (int i = 999; i >= 0; --i) {
        ASSERT_EQ(s.top(), i);
        s.pop();
    }

    ASSERT_TRUE(s.is_empty());
}

TEST(LstStackTest, copy_constructor) {
    lststack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    lststack<int> s2(s1);

    ASSERT_EQ(s2.top(), 30);
    s2.pop();
    ASSERT_EQ(s2.top(), 20);
    s2.pop();
    ASSERT_EQ(s2.top(), 10);
    s2.pop();
    ASSERT_TRUE(s2.is_empty());

    // Original should remain unchanged
    ASSERT_EQ(s1.top(), 30);
    s1.pop();
    ASSERT_EQ(s1.top(), 20);
}

TEST(LstStackTest, assignment_operator) {
    lststack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    lststack<int> s2;
    s2 = s1;

    ASSERT_EQ(s2.top(), 30);
    s2.pop();
    ASSERT_EQ(s2.top(), 20);
    s2.pop();
    ASSERT_EQ(s2.top(), 10);
    s2.pop();
    ASSERT_TRUE(s2.is_empty());

    // Original should remain unchanged
    ASSERT_EQ(s1.top(), 30);
    s1.pop();
    ASSERT_EQ(s1.top(), 20);
}

TEST(LstStackTest, self_assignment) {
    lststack<int> s;
    s.push(10);
    s.push(20);

    s = s;

    ASSERT_EQ(s.top(), 20);
    s.pop();
    ASSERT_EQ(s.top(), 10);
    s.pop();
    ASSERT_TRUE(s.is_empty());
}

TEST(LstStackTest, mixed_operations) {
    lststack<int> s;

    s.push(1);
    s.push(2);
    ASSERT_EQ(s.top(), 2);

    s.pop();
    ASSERT_EQ(s.top(), 1);

    s.push(3);
    ASSERT_EQ(s.top(), 3);

    s.push(4);
    ASSERT_EQ(s.top(), 4);

    s.pop();
    ASSERT_EQ(s.top(), 3);

    s.pop();
    ASSERT_EQ(s.top(), 1);

    s.pop();
    ASSERT_TRUE(s.is_empty());
}