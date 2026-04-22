#pragma once
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "Hash_Table_C.h"
#include "Hash_Table_OA.h"

TEST(HashTableTest, InsertAndFind) {
    HashTableC<int> ht(10);

    ht.insert("daewoo", 100);
    ht.insert("nexia", 200);

    EXPECT_EQ(ht.find("daewoo"), 100);
    EXPECT_EQ(ht.find("nexia"), 200);
    EXPECT_EQ(ht.getSize(), 2);
}

TEST(HashTableTest, InsertDuplicateThrows) {
    HashTableC<int> ht(10);

    ht.insert("nexia", 100);
    EXPECT_THROW(ht.insert("nexia", 200), std::logic_error);
    EXPECT_EQ(ht.find("nexia"), 100);
}

TEST(HashTableTest, FindNonexistentThrows) {
    HashTableC<int> ht(10);

    ht.insert("daewoo", 100);
    EXPECT_THROW(ht.find("nexia"), std::logic_error);
}

TEST(HashTableTest, ReplaceExistingKey) {
    HashTableC<int> ht(10);

    ht.insert("daewoo", 100);
    ht.replace("daewoo", 999);

    EXPECT_EQ(ht.find("daewoo"), 999);
    EXPECT_EQ(ht.getSize(), 1);
}

TEST(HashTableTest, ReplaceNonexistentThrows) {
    HashTableC<int> ht(10);

    ht.insert("daewoo", 100);
    EXPECT_THROW(ht.replace("nexia", 200), std::logic_error);
}

TEST(HashTableTest, EraseExistingKey) {
    HashTableC<int> ht(10);

    ht.insert("daewoo", 100);
    ht.insert("nexia", 200);

    ht.erase("daewoo");

    EXPECT_FALSE(ht.consist("daewoo"));
    EXPECT_TRUE(ht.consist("nexia"));
    EXPECT_EQ(ht.getSize(), 1);
}

TEST(HashTableTest, EraseNonexistentNoThrow) {
    HashTableC<int> ht(10);

    ht.insert("daewoo", 100);
    EXPECT_NO_THROW(ht.erase("nexia"));
    EXPECT_EQ(ht.getSize(), 1);
}

TEST(HashTableTest, EraseThenInsertAgain) {
    HashTableC<int> ht(10);

    ht.insert("daewoo", 100);
    ht.erase("daewoo");
    EXPECT_NO_THROW(ht.insert("daewoo", 200));
    EXPECT_EQ(ht.find("daewoo"), 200);
}

TEST(HashTableTest, Clear) {
    HashTableC<int> ht(10);

    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.insert("c", 3);

    ht.clear();

    EXPECT_TRUE(ht.is_empty());
    EXPECT_EQ(ht.getSize(), 0);
    EXPECT_FALSE(ht.consist("a"));
}

TEST(HashTableTest, IsEmpty) {
    HashTableC<int> ht(10);

    EXPECT_TRUE(ht.is_empty());

    ht.insert("daewoo", 100);
    EXPECT_FALSE(ht.is_empty());

    ht.erase("daewoo");
    EXPECT_TRUE(ht.is_empty());
}

TEST(HashTableTest, MergeTwoTables) {
    std::vector<std::pair<std::string,int>> ht1;
    std::vector<std::pair<std::string, int>> ht2;
    HashTableC<int> result(10);

    ht1.push_back(std::make_pair("apple", 100));
    ht1.push_back(std::make_pair("banana", 200));
    ht1.push_back(std::make_pair("orange", 300));

    ht2.push_back(std::make_pair("grape", 400));
    ht2.push_back(std::make_pair("melon", 800));
    ht2.push_back(std::make_pair("apple", 700));

    for (int i = 0; i < ht1.size(); i++) {
        result.insert(ht1[i].first, ht1[i].second);
    }

    for (int i = 0; i < ht2.size(); i++) {
        try {
            result.insert(ht2[i].first, ht2[i].second);
        }
        catch (...) {}
    }


    EXPECT_EQ(result.getSize(), 5);
    EXPECT_EQ(result.find("apple"), 100);
    EXPECT_EQ(result.find("banana"), 200);
    EXPECT_EQ(result.find("orange"), 300);
    EXPECT_EQ(result.find("grape"), 400);
    EXPECT_EQ(result.find("melon"), 800);
}


//===================================test for hash table OA

TEST(HashTableOATest, InsertAndFind) {
    HashTableOA<int> ht(10);

    ht.insert("daewoo", 100);
    ht.insert("nexia", 200);

    EXPECT_EQ(ht.find("daewoo"), 100);
    EXPECT_EQ(ht.find("nexia"), 200);
    EXPECT_EQ(ht.size(), 2);
}

TEST(HashTableOATest, InsertDuplicateThrows) {
    HashTableOA<int> ht(10);

    ht.insert("nexia", 100);
    EXPECT_THROW(ht.insert("nexia", 200), std::logic_error);
    EXPECT_EQ(ht.find("nexia"), 100);
    EXPECT_EQ(ht.size(), 1);
}

TEST(HashTableOATest, FindNonexistentThrows) {
    HashTableOA<int> ht(10);

    ht.insert("daewoo", 100);
    EXPECT_THROW(ht.find("nexia"), std::logic_error);
}

TEST(HashTableOATest, ReplaceExistingKey) {
    HashTableOA<int> ht(10);

    ht.insert("daewoo", 100);
    ht.replace("daewoo", 999);

    EXPECT_EQ(ht.find("daewoo"), 999);
    EXPECT_EQ(ht.size(), 1);
}

TEST(HashTableOATest, ReplaceNonexistentThrows) {
    HashTableOA<int> ht(10);

    ht.insert("daewoo", 100);
    EXPECT_THROW(ht.replace("nexia", 200), std::logic_error);
}

TEST(HashTableOATest, EraseExistingKey) {
    HashTableOA<int> ht(10);

    ht.insert("daewoo", 100);
    ht.insert("nexia", 200);

    ht.erase("daewoo");

    EXPECT_FALSE(ht.consist("daewoo"));
    EXPECT_TRUE(ht.consist("nexia"));
    EXPECT_EQ(ht.size(), 1);
    EXPECT_NO_THROW(ht.insert("daewoo", 200));
    EXPECT_EQ(ht.find("daewoo"), 200);
    EXPECT_EQ(ht.size(), 2);
}

TEST(HashTableOATest, EraseNonexistentThrows) {
    HashTableOA<int> ht(10);

    ht.insert("daewoo", 100);
    EXPECT_THROW(ht.erase("nexia"), std::logic_error);
    EXPECT_EQ(ht.size(), 1);
}

TEST(HashTableOATest, IsEmpty) {
    HashTableOA<int> ht(10);

    EXPECT_TRUE(ht.is_empty());

    ht.insert("daewoo", 100);
    EXPECT_FALSE(ht.is_empty());

    ht.erase("daewoo");
    EXPECT_TRUE(ht.is_empty());
}

TEST(HashTableOATest, ConsistExistingKey) {
    HashTableOA<int> ht(10);

    ht.insert("daewoo", 100);
    ht.insert("nexia", 200);

    EXPECT_TRUE(ht.consist("daewoo"));
    ht.erase("daewoo");
    EXPECT_FALSE(ht.consist("daewoo"));
    EXPECT_TRUE(ht.consist("nexia"));
    EXPECT_FALSE(ht.consist("matiz"));
}

TEST(HashTableOATest, MultipleInsertions) {
    HashTableOA<int> ht(10);

    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.insert("c", 3);
    ht.insert("d", 4);
    ht.insert("e", 5);

    EXPECT_EQ(ht.size(), 5);
    EXPECT_EQ(ht.find("a"), 1);
    EXPECT_EQ(ht.find("c"), 3);
    EXPECT_EQ(ht.find("e"), 5);
}

TEST(HashTableOATest, RehashWorks) {
    HashTableOA<int> ht(4);

    for (int i = 0; i < 20; i++) {
        ht.insert("key" + std::to_string(i), i);
    }

    EXPECT_EQ(ht.size(), 20);

    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(ht.find("key" + std::to_string(i)), i);
    }
}

TEST(HashTableOATest, DeletedCellsReused) {
    HashTableOA<int> ht(10);


    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.insert("c", 3);

    ht.erase("b");

    // Вставляем новый элемент - должна использоваться deleted ячейка
    ht.insert("d", 4);

    EXPECT_EQ(ht.size(), 3);
    EXPECT_TRUE(ht.consist("a"));
    EXPECT_FALSE(ht.consist("b"));
    EXPECT_TRUE(ht.consist("c"));
    EXPECT_TRUE(ht.consist("d"));
}

TEST(HashTableOATest, ShiftCalculation) {
    HashTableOA<int> ht1(10);
    HashTableOA<int> ht2(20);

    EXPECT_NE(ht1.get_shift(), ht2.get_shift());

    EXPECT_GT(ht1.get_shift(), 0);
    EXPECT_GT(ht2.get_shift(), 0);
}


