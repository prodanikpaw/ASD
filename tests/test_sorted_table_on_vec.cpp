#include <gtest/gtest.h>
#include "Sorted_Table_On_Vec.h"
#include <string>

using namespace std;

TEST(SortedTableTest, EmptyTable) {
    Sorted_Table_On_Vec<int, string> table;

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
    EXPECT_FALSE(table.consist(1));
    EXPECT_EQ(table.find(1), string());
}

TEST(SortedTableTest, InsertOneElement) {
    Sorted_Table_On_Vec<int, string> table;

    table.insert(5, "five");

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.consist(5));
    EXPECT_EQ(table.find(5), "five");
}

TEST(SortedTableTest, InsertMultipleElements) {
    Sorted_Table_On_Vec<int, string> table;

    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");
    table.insert(9, "nine");

    EXPECT_EQ(table.size(), 5);

    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(8));
    EXPECT_TRUE(table.consist(9));

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(8), "eight");
    EXPECT_EQ(table.find(9), "nine");
}

TEST(SortedTableTest, UpdateExistingKey) {
    Sorted_Table_On_Vec<int, string> table;

    table.insert(3, "three");
    EXPECT_EQ(table.find(3), "three");
    EXPECT_EQ(table.size(), 1);

    table.replace(3, "THREE");

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(3), "THREE");
}

TEST(SortedTableTest, ReplaceValue) {
    Sorted_Table_On_Vec<int, string> table;

    table.insert(4, "four");
    table.replace(4, "FOUR");

    EXPECT_EQ(table.find(4), "FOUR");

    table.replace(10, "ten");
    EXPECT_FALSE(table.consist(10));
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTableTest, EraseElement) {
    Sorted_Table_On_Vec<int, string> table;

    table.insert(7, "seven");
    table.insert(3, "three");
    table.insert(5, "five");

    EXPECT_EQ(table.size(), 3);

    table.erase(3);

    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist(3));
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(7));

    table.erase(10);
    EXPECT_EQ(table.size(), 2);
}

TEST(SortedTableTest, FindNonExistentKey) {
    Sorted_Table_On_Vec<int, string> table;

    table.insert(15, "fifteen");
    table.insert(25, "twenty five");

    EXPECT_EQ(table.find(10), string());
    EXPECT_EQ(table.find(20), string());
    EXPECT_EQ(table.find(30), string());
}

TEST(SortedTableTest, ClearTable) {
    Sorted_Table_On_Vec<int, string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 3);

    table.clear();

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
    EXPECT_FALSE(table.consist(1));
}

TEST(SortedTableTest, StringKeys) {
    Sorted_Table_On_Vec<string, int> table;

    table.insert("apple", 5);
    table.insert("banana", 3);
    table.insert("cherry", 8);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist("banana"));
    EXPECT_EQ(table.find("apple"), 5);
    EXPECT_EQ(table.find("cherry"), 8);
    EXPECT_EQ(table.find("grape"), 0);

    table.replace("banana", 10);
    EXPECT_EQ(table.find("banana"), 10);

    table.erase("apple");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("apple"));
}

TEST(SortedTableTest, DoubleKeys) {
    Sorted_Table_On_Vec<double, bool> table;

    table.insert(3.14, true);
    table.insert(2.71, false);
    table.insert(1.61, true);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist(3.14));
    EXPECT_TRUE(table.consist(2.71));
    EXPECT_EQ(table.find(2.71), false);
    EXPECT_EQ(table.find(1.61), true);

    table.erase(3.14);
    EXPECT_EQ(table.size(), 2);
}

TEST(SortedTableTest, MultipleOperations) {
    Sorted_Table_On_Vec<int, string> table;

    for (int i = 0; i < 10; ++i) {
        table.insert(i, "value" + to_string(i));
    }

    EXPECT_EQ(table.size(), 10);

    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), "value" + to_string(i));
    }

    for (int i = 0; i < 10; i += 2) {
        table.erase(i);
    }

    EXPECT_EQ(table.size(), 5);

    for (int i = 1; i < 10; i += 2) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), "value" + to_string(i));
    }

    for (int i = 0; i < 10; i += 2) {
        EXPECT_FALSE(table.consist(i));
    }
}

// Проверка граничных случаев
TEST(SortedTableTest, EdgeCases) {
    Sorted_Table_On_Vec<int, string> table;

    table.erase(1);
    EXPECT_TRUE(table.is_empty());

    table.insert(1, "one");
    table.erase(1);
    EXPECT_TRUE(table.is_empty());

    table.insert(1, "one again");
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(1), "one again");
}

TEST(SortedTableTest, NegativeKeys) {
    Sorted_Table_On_Vec<int, string> table;

    table.insert(-5, "minus five");
    table.insert(0, "zero");
    table.insert(3, "three");
    table.insert(-10, "minus ten");
    // table.insert(5, "five");

    EXPECT_EQ(table.size(), 4);
    EXPECT_TRUE(table.consist(-10));
    EXPECT_TRUE(table.consist(-5));
    EXPECT_TRUE(table.consist(0));
    EXPECT_TRUE(table.consist(3));

    EXPECT_EQ(table.find(-10), "minus ten");
    EXPECT_EQ(table.find(-5), "minus five");

    table.erase(-5);
    EXPECT_FALSE(table.consist(-5));
    EXPECT_EQ(table.size(), 3);
}