#include <gtest/gtest.h>
#include "lstqueue.h"

TEST(LstQueueTest, is_empty_on_creation) {
    lstqueue<int> q;

    ASSERT_TRUE(q.is_empty());
}

TEST(LstQueueTest, push_and_front_operations) {
    lstqueue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);

    ASSERT_EQ(q.front(), 10);
    ASSERT_FALSE(q.is_empty());
}

TEST(LstQueueTest, pop_operations) {
    lstqueue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    ASSERT_EQ(q.front(), 10);
    q.pop();
    ASSERT_EQ(q.front(), 20);
    q.pop();
    ASSERT_EQ(q.front(), 30);
    q.pop();
    ASSERT_TRUE(q.is_empty());
}

TEST(LstQueueTest, clear_operation) {
    lstqueue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    q.clear();

    ASSERT_TRUE(q.is_empty());
}

TEST(LstQueueTest, throw_when_pop_empty_queue) {
    lstqueue<int> q;

    ASSERT_THROW(q.pop(), std::logic_error);
}

TEST(LstQueueTest, throw_when_front_empty_queue) {
    lstqueue<int> q;

    ASSERT_THROW(q.front(), std::logic_error);
}

TEST(LstQueueTest, push_after_clear) {
    lstqueue<int> q;
    q.push(10);
    q.push(20);
    q.clear();

    q.push(40);

    ASSERT_EQ(q.front(), 40);
    ASSERT_FALSE(q.is_empty());
}

TEST(LstQueueTest, works_with_string_type) {
    lstqueue<std::string> q;

    q.push("hello");
    q.push("world");

    ASSERT_EQ(q.front(), "hello");
    q.pop();
    ASSERT_EQ(q.front(), "world");
}

TEST(LstQueueTest, fifo_principle) {
    lstqueue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    ASSERT_EQ(q.front(), 1);
    q.pop();
    ASSERT_EQ(q.front(), 2);
    q.pop();
    ASSERT_EQ(q.front(), 3);
}

TEST(LstQueueTest, multiple_push_pop_operations) {
    lstqueue<int> q;

    for (int i = 0; i < 50; ++i) {
        q.push(i);
        ASSERT_EQ(q.front(), 0);
    }

    for (int i = 0; i < 50; ++i) {
        ASSERT_EQ(q.front(), i);
        q.pop();
    }

    ASSERT_TRUE(q.is_empty());
}

TEST(LstQueueTest, back_operation) {
    lstqueue<int> q;

    q.push(10);
    ASSERT_EQ(q.back(), 10);

    q.push(20);
    ASSERT_EQ(q.back(), 20);

    q.push(30);
    ASSERT_EQ(q.back(), 30);
}

TEST(LstQueueTest, throw_when_back_empty_queue) {
    lstqueue<int> q;

    ASSERT_THROW(q.back(), std::logic_error);
}

TEST(LstQueueTest, large_number_of_elements) {
    lstqueue<int> q;

    for (int i = 0; i < 1000; ++i) {
        q.push(i);
        ASSERT_EQ(q.front(), 0);
    }

    ASSERT_EQ(q.size(), 1000);

    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(q.front(), i);
        q.pop();
    }

    ASSERT_TRUE(q.is_empty());
}

TEST(LstQueueTest, copy_constructor) {
    lstqueue<int> q1;
    q1.push(10);
    q1.push(20);
    q1.push(30);

    lstqueue<int> q2(q1);

    ASSERT_EQ(q2.front(), 10);
    q2.pop();
    ASSERT_EQ(q2.front(), 20);
    q2.pop();
    ASSERT_EQ(q2.front(), 30);

    // Original should remain unchanged
    ASSERT_EQ(q1.front(), 10);
    q1.pop();
    ASSERT_EQ(q1.front(), 20);
}

TEST(LstQueueTest, assignment_operator) {
    lstqueue<int> q1;
    q1.push(10);
    q1.push(20);
    q1.push(30);

    lstqueue<int> q2;
    q2 = q1;

    ASSERT_EQ(q2.front(), 10);
    q2.pop();
    ASSERT_EQ(q2.front(), 20);
    q2.pop();
    ASSERT_EQ(q2.front(), 30);

    // Original should remain unchanged
    ASSERT_EQ(q1.front(), 10);
    q1.pop();
    ASSERT_EQ(q1.front(), 20);
}

TEST(LstQueueTest, self_assignment) {
    lstqueue<int> q;
    q.push(10);
    q.push(20);

    q = q;

    ASSERT_EQ(q.front(), 10);
    q.pop();
    ASSERT_EQ(q.front(), 20);
    q.pop();
    ASSERT_TRUE(q.is_empty());
}

TEST(LstQueueTest, size_operation) {
    lstqueue<int> q;

    ASSERT_EQ(q.size(), 0);

    q.push(10);
    ASSERT_EQ(q.size(), 1);

    q.push(20);
    ASSERT_EQ(q.size(), 2);

    q.pop();
    ASSERT_EQ(q.size(), 1);

    q.pop();
    ASSERT_EQ(q.size(), 0);
}

TEST(LstQueueTest, mixed_operations) {
    lstqueue<int> q;

    q.push(1);
    q.push(2);
    ASSERT_EQ(q.front(), 1);
    ASSERT_EQ(q.back(), 2);

    q.pop();
    ASSERT_EQ(q.front(), 2);
    ASSERT_EQ(q.back(), 2);

    q.push(3);
    ASSERT_EQ(q.front(), 2);
    ASSERT_EQ(q.back(), 3);

    q.push(4);
    ASSERT_EQ(q.front(), 2);
    ASSERT_EQ(q.back(), 4);

    q.pop();
    ASSERT_EQ(q.front(), 3);
    ASSERT_EQ(q.back(), 4);
}

TEST(LstQueueTest, works_with_double_type) {
    lstqueue<double> q;

    q.push(3.14);
    q.push(2.71);

    ASSERT_DOUBLE_EQ(q.front(), 3.14);
    q.pop();
    ASSERT_DOUBLE_EQ(q.front(), 2.71);
}