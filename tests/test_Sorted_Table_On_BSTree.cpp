#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "Sorted_Table_On_BSTree.h"

TEST(SortedBSTreeTableTest, EmptyTree) {
    SortedBSTreeTable<int, std::string> table;

    EXPECT_TRUE(table.is_empty());
}

TEST(SortedBSTreeTableTest, InsertOneElement) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(5, "five");

    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(5));
    EXPECT_EQ(table.find(5), "five");
}

TEST(SortedBSTreeTableTest, InsertMultipleElements) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(2, "two");
    table.insert(4, "four");

    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(7));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(4));
}

TEST(SortedBSTreeTableTest, FindExistingKey) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");

    EXPECT_EQ(table.find(10), "ten");
    EXPECT_EQ(table.find(20), "twenty");
    EXPECT_EQ(table.find(30), "thirty");
}

TEST(SortedBSTreeTableTest, FindNonExistingKey) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");

    EXPECT_THROW(table.find(30), std::out_of_range);
    EXPECT_THROW(table.find(999), std::out_of_range);
}

TEST(SortedBSTreeTableTest, ConsistKey) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");

    EXPECT_TRUE(table.consist(10));
    EXPECT_TRUE(table.consist(20));
    EXPECT_FALSE(table.consist(30));
    EXPECT_FALSE(table.consist(999));
}

TEST(SortedBSTreeTableTest, UpdateExistingKey) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(5, "five");

    table.insert(5, "FIVE");
    EXPECT_EQ(table.find(5), "five");

    table.replace(5, "FIVE");
    EXPECT_EQ(table.find(5), "FIVE");
}

TEST(SortedBSTreeTableTest, EraseLeaf) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(1, "one");
    table.insert(4, "four");

    table.erase(4);
    EXPECT_FALSE(table.consist(4));
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(7));
    EXPECT_TRUE(table.consist(1));
}

TEST(SortedBSTreeTableTest, EraseNodeWithOneChild) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(1, "one");
    table.insert(4, "four");
    table.insert(6, "six");

    table.erase(7);
    EXPECT_FALSE(table.consist(7));
    EXPECT_TRUE(table.consist(6));
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(3));
}

TEST(SortedBSTreeTableTest, EraseNodeWithTwoChildren) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(1, "one");
    table.insert(4, "four");
    table.insert(6, "six");
    table.insert(8, "eight");

    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(7));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(4));
    EXPECT_TRUE(table.consist(6));
    EXPECT_TRUE(table.consist(8));
}

TEST(SortedBSTreeTableTest, EraseOnlyNode) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(42, "answer");

    table.erase(42);
    EXPECT_TRUE(table.is_empty());
    EXPECT_FALSE(table.consist(42));
}

TEST(SortedBSTreeTableTest, EraseNonExisting) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(5, "five");
    table.insert(10, "ten");

    EXPECT_THROW(table.erase(999), std::out_of_range);
}

TEST(SortedBSTreeTableTest, ManyElements) {
    SortedBSTreeTable<int, int> table;

    for (int i = 0; i < 100; i++) {
        table.insert(i, i * i);
    }

    for (int i = 0; i < 100; i++) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), i * i);
    }
}

TEST(SortedBSTreeTableTest, EraseAllElements) {
    SortedBSTreeTable<int, std::string> table;

    for (int i = 0; i < 10; i++) {
        table.insert(i, "value" + std::to_string(i));
    }

    for (int i = 0; i < 10; i++) {
        table.erase(i);
    }

    EXPECT_TRUE(table.is_empty());
}

TEST(SortedBSTreeTableTest, ComplexScenario) {
    SortedBSTreeTable<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(2, "two");
    table.insert(4, "four");

    table.erase(7);
    EXPECT_FALSE(table.consist(7));

    table.erase(5);
    EXPECT_FALSE(table.consist(5));

    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(4));

    table.insert(8, "eight");
    table.insert(9, "nine");

    EXPECT_TRUE(table.consist(8));
    EXPECT_TRUE(table.consist(9));
}

TEST(SortedBSTreeTableTest, ReplaceNonExistingKey) {
    SortedBSTreeTable<int, std::string> table;
    table.insert(5, "five");

    EXPECT_THROW(table.replace(10, "ten"), std::out_of_range);
}

TEST(SortedBSTreeTableTest, FindInEmptyTree) {
    SortedBSTreeTable<int, std::string> table;

    EXPECT_THROW(table.find(5), std::out_of_range);
}

TEST(SortedBSTreeTableTest, EraseInEmptyTree) {
    SortedBSTreeTable<int, std::string> table;

    EXPECT_THROW(table.erase(5), std::out_of_range);
}

TEST(SortedBSTreeTableTest, InsertDuplicateKey) {
    SortedBSTreeTable<int, std::string> table;
    table.insert(5, "five");

    table.insert(5, "FIVE");
    EXPECT_EQ(table.find(5), "five");
}