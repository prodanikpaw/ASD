#include <gtest/gtest.h>
#include "Unsorted_Table_On_Tree.h"
#include <string>


TEST(UnorderedTreeTableTest, EmptyTable) {
    UnorderedTreeTable<int, std::string> table;

    EXPECT_EQ(table.size(), 0);
    EXPECT_TRUE(table.empty());
}

TEST(UnorderedTreeTableTest, InsertAndEraseMultipleElements) {
    UnorderedTreeTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist(2));
}