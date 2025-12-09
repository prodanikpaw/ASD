#include <gtest/gtest.h>
#include "Queue.h"


TEST(QueueTest, is_empty_on_creation) {

    queue<int> q;


    ASSERT_TRUE(q.is_empty());
    ASSERT_FALSE(q.is_full());
}

TEST(QueueTest, push_and_head_operations) {

    queue<int> q;


    q.push(10);
    q.push(20);
    q.push(30);


    ASSERT_EQ(q.head(), 10);
    ASSERT_FALSE(q.is_empty());
}

TEST(QueueTest, pop_operations) {

    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);


    ASSERT_EQ(q.head(), 10);
    q.pop();
    ASSERT_EQ(q.head(), 20);
    q.pop();
    ASSERT_EQ(q.head(), 30);
    q.pop();
    ASSERT_TRUE(q.is_empty());
}

TEST(QueueTest, clear_operation) {

    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    q.clear();


    ASSERT_TRUE(q.is_empty());
}

TEST(QueueTest, throw_when_pop_empty_queue) {

    queue<int> q;


    ASSERT_THROW(q.pop(), std::logic_error);
}

TEST(QueueTest, throw_when_head_empty_queue) {

    queue<int> q;


    ASSERT_THROW(q.head(), std::logic_error);
}

TEST(QueueTest, push_after_clear) {

    queue<int> q;
    q.push(10);
    q.push(20);
    q.clear();


    q.push(40);


    ASSERT_EQ(q.head(), 40);
    ASSERT_FALSE(q.is_empty());
}

TEST(QueueTest, works_with_string_type) {

    queue<std::string> q;


    q.push("hello");
    q.push("world");


    ASSERT_EQ(q.head(), "hello");
    q.pop();
    ASSERT_EQ(q.head(), "world");
}

TEST(QueueTest, fifo_principle) {

    queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    ASSERT_EQ(q.head(), 1);
    q.pop();
    ASSERT_EQ(q.head(), 2);
    q.pop();
    ASSERT_EQ(q.head(), 3);
}

TEST(QueueTest, multiple_push_pop_operations) {

    queue<int> q;


    for (int i = 0; i < 50; ++i) {
        q.push(i);
        ASSERT_EQ(q.head(), 0);
    }

    for (int i = 0; i < 50; ++i) {
        ASSERT_EQ(q.head(), i);
        q.pop();
    }

    ASSERT_TRUE(q.is_empty());
}

TEST(QueueTest, is_full_detection) {

    queue<int> q;

    for (int i = 0; i < 100; ++i) {
        q.push(i);
    }

    ASSERT_TRUE(q.is_full());
}

TEST(QueueTest, throw_when_push_full_queue) {

    queue<int> q;

    for (int i = 0; i < 100; ++i) {
        q.push(i);
    }


    ASSERT_THROW(q.push(101), std::logic_error);
}

TEST(QueueTest, circular_buffer_behavior) {

    queue<int> q;

    for (int i = 0; i < 100; ++i) {
        q.push(i);
    }

    for (int i = 0; i < 50; ++i) {
        q.pop();
    }

    for (int i = 100; i < 150; ++i) {
        q.push(i);
    }


    ASSERT_TRUE(q.is_full());
    ASSERT_EQ(q.head(), 50);
}