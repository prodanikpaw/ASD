#include <gtest/gtest.h>
#include <string>
#include "Skiplist.h"

TEST(SkipListSimpleTest, BasicOperations) {

    SkipList<std::string, double> skipList(5);


    EXPECT_EQ(skipList.getCurrentLevel(), 0);
    EXPECT_EQ(skipList.getMaxLevel(), 5);

    skipList.insert("key1", 12.15);
    skipList.insert("key2", 4.0);
    skipList.insert("key3", 15.3);

    auto found1 = skipList.find("key1");
    auto found2 = skipList.find("key2");
    auto found3 = skipList.find("key3");

    ASSERT_NE(found1, nullptr);
    ASSERT_NE(found2, nullptr);
    ASSERT_NE(found3, nullptr);

    EXPECT_EQ(found1->data.first, "key1");
    EXPECT_EQ(found2->data.first, "key2");
    EXPECT_EQ(found3->data.first, "key3");

    EXPECT_DOUBLE_EQ(found1->data.second, 12.15);
    EXPECT_DOUBLE_EQ(found2->data.second, 4.0);
    EXPECT_DOUBLE_EQ(found3->data.second, 15.3);

    auto notFound = skipList.find("key999");
    EXPECT_EQ(notFound, nullptr);

    skipList.insert("key2", 5.5);
    auto updated = skipList.find("key2");
    ASSERT_NE(updated, nullptr);
    EXPECT_DOUBLE_EQ(updated->data.second, 5.5);

    EXPECT_DOUBLE_EQ(skipList.find("key1")->data.second, 12.15);
    EXPECT_DOUBLE_EQ(skipList.find("key3")->data.second, 15.3);
}

TEST(SkipListSimpleTest, LevelTest) {
    SkipList<std::string, int> list(5);

    list.insert("low", 100, 0);
    list.insert("mid", 200, 2);  
    list.insert("high", 300, 4);

    auto low = list.find("low");
    auto mid = list.find("mid");
    auto high = list.find("high");

    ASSERT_NE(low, nullptr);
    ASSERT_NE(mid, nullptr);
    ASSERT_NE(high, nullptr);

    EXPECT_EQ(low->level, 0);
    EXPECT_EQ(mid->level, 2);
    EXPECT_EQ(high->level, 4);

    EXPECT_GE(list.getCurrentLevel(), 4);
}