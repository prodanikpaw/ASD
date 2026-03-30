#include <gtest/gtest.h>
#include "Table_On_List.h"

TEST(UnsortedTableOnListTest, CreationAndEmpty) {
    UnsortedTableOnList<int, std::string> table;

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(UnsortedTableOnListTest, Insert) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST(UnsortedTableOnListTest, Find) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
}

TEST(UnsortedTableOnListTest, FindNonExistent) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");

    EXPECT_THROW(table.find(999), std::invalid_argument);
}

TEST(UnsortedTableOnListTest, InsertDuplicate) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");

    EXPECT_THROW(table.insert(1, "another one"), std::invalid_argument);
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(1), "one");
}

TEST(UnsortedTableOnListTest, Erase) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.erase(2);

    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));

    table.erase(1);
    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.consist(3));

    table.erase(3);
    EXPECT_TRUE(table.is_empty());
}

TEST(UnsortedTableOnListTest, EraseNonExistent) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");

    EXPECT_THROW(table.erase(999), std::invalid_argument);
    EXPECT_EQ(table.size(), 1);
}

TEST(UnsortedTableOnListTest, Replace) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");

    table.replace(1, "ONE");
    table.replace(2, "TWO");

    EXPECT_EQ(table.find(1), "ONE");
    EXPECT_EQ(table.find(2), "TWO");
}

TEST(UnsortedTableOnListTest, ReplaceNonExistent) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");

    EXPECT_THROW(table.replace(999, "anything"), std::invalid_argument);
    EXPECT_EQ(table.find(1), "one");
}

TEST(UnsortedTableOnListTest, Consist) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_FALSE(table.consist(3));
    EXPECT_FALSE(table.consist(4));
}

TEST(UnsortedTableOnListTest, Clear) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.size(), 3);

    table.clear();

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
    EXPECT_FALSE(table.consist(1));
}

TEST(UnsortedTableOnListTest, CopyConstructor) {
    UnsortedTableOnList<int, std::string> original;
    original.insert(1, "one");
    original.insert(2, "two");

    UnsortedTableOnList<int, std::string> copy(original);

    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.find(1), "one");
    EXPECT_EQ(copy.find(2), "two");

    copy.replace(1, "ONE");
    EXPECT_EQ(original.find(1), "one");
    EXPECT_EQ(copy.find(1), "ONE");
}

TEST(UnsortedTableOnListTest, AssignmentOperator) {
    UnsortedTableOnList<int, std::string> table1;
    table1.insert(1, "one");
    table1.insert(2, "two");

    UnsortedTableOnList<int, std::string> table2;
    table2.insert(3, "three");

    table2 = table1;

    EXPECT_EQ(table2.size(), 2);
    EXPECT_EQ(table2.find(1), "one");
    EXPECT_EQ(table2.find(2), "two");
    EXPECT_FALSE(table2.consist(3));

    table2 = table2;
    EXPECT_EQ(table2.size(), 2);
    EXPECT_EQ(table2.find(1), "one");
}

TEST(UnsortedTableOnListTest, StringKeys) {
    UnsortedTableOnList<std::string, int> table;

    table.insert("apple", 5);
    table.insert("banana", 3);
    table.insert("orange", 8);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist("banana"));
    EXPECT_EQ(table.find("apple"), 5);
    EXPECT_EQ(table.find("orange"), 8);

    table.replace("orange", 10);
    EXPECT_EQ(table.find("orange"), 10);

    table.erase("banana");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("banana"));
}

TEST(UnsortedTableOnListTest, EmptyTableOperations) {
    UnsortedTableOnList<int, std::string> table;

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
    EXPECT_FALSE(table.consist(1));

    EXPECT_THROW(table.find(1), std::invalid_argument);
    EXPECT_THROW(table.erase(1), std::invalid_argument);
    EXPECT_THROW(table.replace(1, "anything"), std::invalid_argument);

    std::stringstream ss;
    EXPECT_NO_THROW(table.print(ss));
}

TEST(UnsortedTableOnListTest, SequenceOfOperations) {
    UnsortedTableOnList<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_EQ(table.size(), 2);

    table.replace(1, "ONE");
    EXPECT_EQ(table.find(1), "ONE");

    EXPECT_TRUE(table.consist(2));
    EXPECT_FALSE(table.consist(3));

    table.erase(2);
    EXPECT_EQ(table.size(), 1);
    EXPECT_FALSE(table.consist(2));

    table.insert(3, "three");
    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table.find(1), "ONE");
    EXPECT_EQ(table.find(3), "three");
}