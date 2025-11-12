#include <gtest/gtest.h>
#include "list.h"

TEST(ListTest, default_constructor_creates_empty_list) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, push_front_adds_to_beginning) {
    List<int> list;
    list.push_front(10);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);

    list.push_front(20);
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, push_back_adds_to_end) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, pop_front_removes_from_beginning) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_front();
    EXPECT_EQ(list.size(), 2);

    list.pop_front();
    EXPECT_EQ(list.size(), 1);

    list.pop_front();
    EXPECT_TRUE(list.is_empty());
}

TEST(ListTest, pop_back_removes_from_end) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_back();
    EXPECT_EQ(list.size(), 2);

    list.pop_back();
    EXPECT_EQ(list.size(), 1);

    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

TEST(ListTest, insert_at_position_works_correctly) {
    List<int> list;
    list.push_back(10);
    list.push_back(30);

    list.insert(1, 20);
    EXPECT_EQ(list.size(), 3);
}

TEST(ListTest, find_returns_correct_node) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    Node<int>* found = list.find(20);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->value, 20);

    found = list.find(40);
    EXPECT_EQ(found, nullptr);
}

TEST(ListTest, copy_constructor_creates_deep_copy) {
    List<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    List<int> copy(original);
    EXPECT_EQ(copy.size(), 3);

    original.pop_front();
    EXPECT_EQ(original.size(), 2);
    EXPECT_EQ(copy.size(), 3);
}

TEST(ListTest, assignment_operator_works_correctly) {
    List<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    List<int> list2;
    list2.push_back(30);
    list2.push_back(40);
    list2.push_back(50);

    list2 = list1;
    EXPECT_EQ(list2.size(), 2);
}

TEST(ListTest, pop_by_node_removes_specific_element) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    Node<int>* nodeToRemove = list.find(20);
    list.pop(nodeToRemove);

    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, complex_operations_sequence) {
    List<int> list;

    list.push_front(2);
    list.push_back(3);
    list.push_front(1);

    EXPECT_EQ(list.size(), 3);

    list.pop_front();
    list.pop_back();

    EXPECT_EQ(list.size(), 1);

    list.pop_front();
    EXPECT_TRUE(list.is_empty());
}

TEST(ListTest, edge_cases_and_error_handling) {
    List<int> list;

    list.pop_front();
    list.pop_back();

    EXPECT_TRUE(list.is_empty());

    list.push_back(42);
    list.pop_back();
    EXPECT_TRUE(list.is_empty());

    EXPECT_THROW(list.insert(5, 100), std::out_of_range);
    EXPECT_THROW(list.pop(5), std::out_of_range);
}


TEST(Iterator_test, can_read) {
    List<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i + 1);
    }
    int expected_val = 1;
    for (List<int>::Iterator it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }
}


